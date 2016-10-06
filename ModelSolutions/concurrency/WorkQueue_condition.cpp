
/*
 *  Compile: make WorkQueue_condition CXXFLAGS=-std=c++1y
 */


#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <future>
#include <deque>
#include <vector>
#include <condition_variable>

using namespace std;

template <class T>
class WorkQueue 
{
public:
    WorkQueue() : 
        running(true),
        t(&WorkQueue::run, this),
        queue(),
        sync(),
        cv()
        {}

    ~WorkQueue() {
        running = false;
        cv.notify_one();
        t.join();
    }

    auto submit(packaged_task<T>&& t) {
        auto future = t.get_future();
        {
            lock_guard<mutex> l(sync);
            queue.emplace_back(std::move(t));
        }
        cv.notify_one();
        return future;
    }

private:
    atomic<bool> running;
    thread t;
    deque<packaged_task<T> > queue;
    mutex sync;
    condition_variable cv;

    
    void run() {
        deque<packaged_task<T> > local_queue;
        while (running) 
        {
            // Run them all
            for (auto& task : local_queue)
                task();
            local_queue.clear();

            unique_lock<mutex> l(sync);
            if (queue.empty())  // don't wait if there's stuff todo
                cv.wait(l, [=]{ return !queue.empty() || !running; });  
            swap(local_queue, queue); 
        }
    } 
};
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
