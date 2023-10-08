#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <memory>
#include <vector>
#include <cassert>

int need { 0 };
int count = { 0 };
std::condition_variable cv;
std::mutex mtx;

void print_left() {

    while (true) {
        std::unique_lock<std::mutex> lock { mtx };
        // while (!(count != need)) cv.wait(lock); 与下面的是等价的
        while (count == need) cv.wait(lock); // 如果满足了这个条件，那么就必须要进行wait，
        assert(count <= need && count >= 0);
        std::cout << '(';
        count++;
        cv.notify_all();
    }

}
void print_right() {
    while (true) {
        std::unique_lock<std::mutex> lock { mtx };
        // while(!(count != 0)) cv.wait(lock); 与下面是等价的
        while (count == 0) cv.wait(lock); // 满足和这个条件，就必须要wait
        assert(count <= need && count >= 0);
        std::cout << ')';                  
        count--;
        cv.notify_all();
    }
}
int main(int argc, char* argv[]) {
    need = std::stoi(argv[1]);
    // need = 1;
    std::vector<std::thread> vec_thread;
    for (int i = 0; i < 100; i++) {
       vec_thread.push_back(std::thread(print_left));
       vec_thread.push_back(std::thread(print_right));
    }
    for (auto &item: vec_thread) item.join();
}