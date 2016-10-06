/*
 * Some remarks:
 *   - hold the lock for the least amount of time
 *     critical section is kept as minimal as possible
 *   - notice the usage of the swap!
 *   - there's always one deque for the user, the work is done on the other one???
 *   - note we don't keep the lock while doing the task, (otherwise deadlock if one task starts another task?)
 *   - See C++ concurrent book.
 *   - sometimes by taking the time for a copy, you might avoid having to take a lock for a time.
 *   - better use a condition variable instead of a sleep (sleep until you get a signal, wake up and continue)
 *     condition variable that will only wake up the thread when new work is available
 */
#include <deque>
#include <future>
#include <thread>
#include <chrono>
using std::literals::chrono_literals;

class WorkQueue {

public:

    WorkQueue()
    {
        std::thread t( [](){
            std::this_thread::sleep_for(2s);
            if (!d.empty())
            {
                std::packaged_task<int()> task = d.pop_front();
                task();
            }
        }
        );
    }

    ~WorkQueue()
    {
    }

    std::future<int> submit(std::packaged_task<int()> task)
    {
        d.push_back(task);  // Needs to take lock!
        return task.get_future();
    }

private:
    std::deque<std::packaged_task<int()>> d;

};


int main()
{
    WorkQue queue;

    std::packaged_task<int()> task( [](int a) { return 99; } );
    queue.submit(task);
}
