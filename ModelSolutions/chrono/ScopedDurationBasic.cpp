
#include <thread>
#include <iostream>
#include <chrono>
using namespace std::chrono;
using namespace std;

struct ScopedDurationLogger
{
    time_point<high_resolution_clock> start;
    int id;

    ScopedDurationLogger(int i) :
        start(high_resolution_clock::now()),
        id(i)
        {}

    ~ScopedDurationLogger() {
        auto end = high_resolution_clock::now();
        duration<double> dur = end - start;
        auto durns = duration_cast<nanoseconds>(dur);
        cout << "It took " << durns.count() << " seconds in " << id << endl;
    }
};

int main()
{
    ScopedDurationLogger logger(1);

    //this_thread::sleep_for(5s);
    {
        ScopedDurationLogger logger2(2);
        //  this_thread::sleep_for(1s);
        //this_thread::sleep_for(4s);
    }
    this_thread::sleep_for(2s);

    // high_resolution_clock::period p;
    // cout << p.num << "/" << p.den << endl;
}
