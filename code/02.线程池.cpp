#include <cmath>
#include <condition_variable>
#include <cstddef>
#include <functional>
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <memory>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>
#include <cassert>
#include <future>

template <typename T>
class SafeQueue
{
public:
    SafeQueue() = default;

    size_t size() 
    { 
        std::lock_guard<std::mutex> guard { m_mtx };
        return m_queue.size(); 
    }
    
    void push(T&& val)
    {
        std::lock_guard<std::mutex> guard { m_mtx };
        m_queue.emplace(std::forward<T>(val));    
    }
    bool empty() 
    {
        std::lock_guard<std::mutex> guard { m_mtx }; 
        return m_queue.empty(); 
    }
    void pop()
    {
        std::lock_guard<std::mutex> guard { m_mtx };
        m_queue.pop();
    }
    
    T& front()
    {
        std::lock_guard<std::mutex> guard { m_mtx };
        return m_queue.front();
    }
private:
    std::queue<T> m_queue;
    std::mutex m_mtx;
};

// 智能指针需要一个完全相同的接口,这时候我们可以两次封装一个类,所以这里采用虚函数的调用方法
class Task
{
public:
    Task() = default;

    template <class Func>
	explicit Task(Func&& f) : m_ptr { std::make_unique<Wrapper<Func>>(std::move(f)) } { }
    void operator() () { m_ptr->call(); }
private:
    class Wrapper_Base 
    {
    public:
        virtual void call() = 0;
        virtual ~Wrapper_Base() = default;
    };

    template<typename Func>
    class Wrapper: public Wrapper_Base
    {
    public:
        explicit Wrapper(Func&& f) : m_func{ std::move(f) } {}
        virtual void call() override { m_func(); }
    private:
        Func m_func; // 最终调用的是这个
    };
    
private:
    std::unique_ptr<Wrapper_Base> m_ptr;
};

class ThreadPool
{
public:
    ThreadPool(size_t thread_size, size_t queue_size) 
        : m_is_running { false }, m_safe_queue_size { queue_size }
    {
        m_threads.reserve(thread_size);
    }

    ~ThreadPool() { stop(); }
    
    void init()
    {
        if (m_is_running) return;
        m_is_running = true;
        int n = m_threads.capacity();

        while (n--)
        {   
            // 这里就是线程池的第二种创建方法，第一个是函数，第二个是这个函数的第一个参数，参考 《深入探索c++对象模型》
            m_threads.emplace_back(&ThreadPool::worker,this); 
        }
    }
    
    // 提交函数
    template<typename Func, typename Ret = std::invoke_result_t<Func>>
    auto submit(Func func) -> std::future<Ret>
    {
        std::packaged_task<Ret()> pt { std::move(func) }; // 以便稍后进行调用
        auto ret = pt.get_future(); // 得到未来的期望
        Task task { std::move(pt)} ;

            {
                std::unique_lock<std::mutex> lock { m_mtx };
                // m_is_not_full.wait(lock, [this] { return (!m_is_running || !(m_safe_queue.size() == m_safe_queue_size));});
                while (m_is_running && (m_safe_queue.size() == m_safe_queue_size)) m_is_not_full.wait(lock);
                assert(m_safe_queue.size() < m_safe_queue_size || !m_is_running);
                if (!m_is_running) return {};
                m_safe_queue.push(std::move(task));
                m_is_not_empty.notify_one(); // 唤醒一个线程去处理他
                
            }
        return ret;

    }
    void stop()
    {
        if (!m_is_running) return;
        call_stop();

        for (auto& item : m_threads)
        {
            if (item.joinable()) item.join();
        }
    }
private:

    void call_stop()
    {
        std::lock_guard<std::mutex> lock_guard { m_mtx };
        m_is_running = false;
        // 唤醒所有的线程将任务处理完成
        m_is_not_full.notify_all();  
        m_is_not_empty.notify_all();
    }

    void worker()
    {
        while (true)
        {
            Task t;
            {
                std::unique_lock<std::mutex> lock { m_mtx };
                while (m_is_running && m_safe_queue.empty() ) m_is_not_empty.wait(lock);
                // m_is_not_empty.wait(lock, [this] { return !m_is_running || !m_safe_queue.empty(); });
                
                if (!m_is_running) return; // 逆天
                t = std::move(m_safe_queue.front());
        
                m_safe_queue.pop();
                m_is_not_full.notify_one();
            }
            t();
        }
    }

private:

    std::vector<std::thread> m_threads; // 保存线程的队列
    std::condition_variable m_is_not_full; 
    std::condition_variable m_is_not_empty;
    std::mutex m_mtx;
    SafeQueue<Task> m_safe_queue ;
    size_t m_safe_queue_size { 0 };
    bool m_is_running { false }; 

};
int main()
{
    ThreadPool pool{ 10, 3};
	
    pool.init();

	std::vector<std::future<long long>> rets;
    
	for (int i = 0; i < 100; i++) 
    {
		auto ret = pool.submit([i] 
        { 
            return 1ll* i * i * i; 
        });
		rets.push_back(std::move(ret));
	}
    for (auto &item : rets)
    {
        item.wait();
        std::cout << item.get() << std::endl; // 如果那个线程没有完全执行完毕，那么这里就会阻塞当前的IO
    }
    std::cout << "yes" << std::endl;
}