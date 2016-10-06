
/*
 *  Compile: make WorkQueue CXXFLAGS=-std=c++1y
 */


#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <future>
#include <deque>
#include <vector>

using namespace std;

template <class T>
class WorkQueue 
{
public:
    WorkQueue();
    ~WorkQueue();

    auto submit(packaged_task<T>&& t) {
        cout << "submit!" << endl; // Unsynchronized prints!

        auto future = t.get_future();
        lock_guard<mutex> l(sync);
        queue.emplace_back(std::move(t));
        return future;
    }

private:
    void run();
    
    atomic<bool> running;
    thread t;
    deque<packaged_task<T> > queue;
    mutex sync;
};
//--------------------------------------------------------------------------------
template<class T>
void WorkQueue<T>::run()
{
    deque<packaged_task<T> > local_queue;
    while (running) {
        {
            lock_guard<mutex> l(sync);
            swap(local_queue, queue);  // Steal the tasks, keeping critical section short in time
                                       // This might increase latency in combination with the sleep(1ms)
        }

        // Run them all
        for (auto& task : local_queue)
            task();
        local_queue.clear();

        cout << "sleeping" << endl;
        this_thread::sleep_for(1ms);
    }
}
//--------------------------------------------------------------------------------
template <class T>
WorkQueue<T>::WorkQueue() : 
    running(true),
    t(&WorkQueue::run, this),
    queue(),
    sync() 
{}
//--------------------------------------------------------------------------------
template <class T>
WorkQueue<T>::~WorkQueue()
{
    running = false;
    t.join();
}
//--------------------------------------------------------------------------------
int main() {
    WorkQueue<thread::id()> wq;
    vector<decltype(wq.submit(packaged_task<thread::id()>()))> futures;

    for(int i=0; i<10; ++i)
        futures.push_back(wq.submit(packaged_task<thread::id()>([]{  return this_thread::get_id();   })));

    for (auto& f : futures)
        cout << f.get() << endl;

    cout << "Main thread id = " << this_thread::get_id() << endl; 
}
//--------------------------------------------------------------------------------
