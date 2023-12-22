# Thread_Pool

- 生产者，消费者模型
- Task利用了一个多态的思想，将不同返回值的future都可以直接放到同一个Wrapper里面，然后让多态直接管理
- 条件变量的wait函数感觉有一点点绕口，改成 while() 就差不多了
- `m_threads.emplace_back(&ThreadPool::worker, this);`: 这个 this 是相当于给这个 worker传入一个参数

```c++
#include <cassert>
#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>
#include <type_traits>
#include <vector>
#include <thread>
#include <future>
#include <iostream>
#include "boost/circular_buffer.hpp"

namespace my_code {
class ThreadPool {

    class Task {
    public:
        Task() = default;
        // 为什么不注释这个析构函数就不行了？？？？？？wc
        // ~Task() = default;

        template <class Fun> Task(Fun&& f) : m_ptr { new Wrapper(std::move(f)) } {}

        void operator()() { m_ptr->call(); }

    private:
        class WrapperBase {
        public:
            virtual void call() = 0;
            virtual ~WrapperBase() = default;
        };

        template <typename Fun> class Wrapper : public WrapperBase {
        public:
            explicit Wrapper(Fun&& f) : m_func(std::move(f)) {}
            virtual void call() override { m_func(); }
            ~Wrapper() = default;

        private:
            Fun m_func;
        };

        std::unique_ptr<WrapperBase> m_ptr;
    };

public:
    ThreadPool(size_t queue_size) : m_queue(queue_size), m_is_running(false) {}
    ~ThreadPool() { stop(); }

    void start(size_t threads_size) {
        if (m_is_running) {
            return;
        }

        m_is_running = true;
        m_threads.reserve(threads_size);

        // 创建线程,并且开始线程
        while (threads_size--) {
            m_threads.emplace_back(&ThreadPool::worker, this);
        }
    }

    void stop() {
        if (!m_is_running) {
            return;
        }
        m_is_running = false;
        m_not_full.notify_all();
        m_not_empty.notify_all();
        for (auto& item : m_threads) {
            if (item.joinable()) {
                item.join();
            }
        }
    }

    template <typename Fun, typename Ret = std::invoke_result_t<Fun>>
    auto submit(Fun&& func) -> std::future<Ret> {
        // 包装一个可以用的函数，然后得到他的 future,就可以了
        std::packaged_task<Ret()> pt { std::move(func) };
        std::future<Ret> ret = pt.get_future();

        Task task(std::move(pt));

        {
            std::unique_lock<std::mutex> lock { m_mtex };

            // m_not_full.wait(lock, [this] { return !m_is_running || !m_queue.full(); });
            
            // 在运行的状态下是满的，那么就等待
            while(m_is_running && m_queue.full()) {
                m_not_full.wait(lock);
            }

            assert(m_is_running);
            assert(!m_queue.full());

            if (!m_is_running) {
                return {};
            }
            m_queue.push_back(std::move(task));
            m_not_empty.notify_one();
        }

        return ret;
    }

private:
    // 相当于轮询
    void worker() {
        while (true) {
            Task t;
            {
                std::unique_lock lock { m_mtex };
                // m_not_empty.wait(lock,
                //                  [this] { return !m_is_running || !m_queue.empty(); });
                // 在运行的状态下为空，那么就等待
                while (m_is_running && m_queue.empty()) {
                    m_not_empty.wait(lock);
                }
                
                assert(!m_is_running || !m_queue.empty());

                if (!m_is_running) {
                    return;
                }

                t = std::move(m_queue.front());
                m_queue.pop_front();
                m_not_full.notify_one();
            }

            t();
        }
    }

private:
    boost::circular_buffer<Task> m_queue; // 任务队列
    std::vector<std::thread> m_threads;   // 线程
    std::mutex m_mtex;                    // 锁
    std::condition_variable m_not_full;  // 条件变量，使得不是满的
    std::condition_variable m_not_empty; // 条件变量，使得不是空的

    bool m_is_running { false }; // 是否停止
};
} // namespace my_code
int main() {
    my_code::ThreadPool pool { 10 };
    pool.start(3);

    std::vector<std::future<int>> rets;

    for (int i = 0; i < 10000; i++) {
        auto ret = pool.submit([i] {
            std::cout << std::this_thread::get_id() << ' ' << std::endl;
            return i;
        });
        rets.push_back(std::move(ret));
    }

    for (auto& ret : rets) {
        std::cout << ret.get() << " ";
    }
}
```


