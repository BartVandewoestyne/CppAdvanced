// TODO: isn't it strange that things get executed sequentially?
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <chrono>
using namespace std::chrono_literals;

int main()
{
    const int NB_THREADS = 10;

    std::mutex m;  // to protect stdout
    std::vector<std::thread> vec;

    for (int i = 0; i < NB_THREADS; ++i)
    {
        // Method 1
        std::thread t([&m](int id){
            {
            std::lock_guard<std::mutex> lock(m);
            std::cout << "Hello from thread " << id << " (" << std::this_thread::get_id() << ").\n";
            }
            std::this_thread::sleep_for(2s);
        }, i);
        vec.push_back(std::move(t));

        // Method 2
        vec.emplace_back([&m](int id){
            {
            std::lock_guard<std::mutex> lock(m);
            std::cout << "Hello from thread " << id << " (" << std::this_thread::get_id() << ").\n";
            }
            std::this_thread::sleep_for(2s);
        }, i);  // note that i is passed as an argument to the lambda from the thread.

    }

    for (auto& t : vec)
    {
        t.join();
    }
}
