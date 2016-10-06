

#include <iostream>
#include <chrono>
#include <thread>

#include "ScopedDuration.hpp"

using namespace std;

int main()
{
    {
        ScopedDurationLogger sd("main");
        this_thread::sleep_for(chrono::seconds(1));
        
        ScopedDurationLogger sd2("smaller main");
        this_thread::sleep_for(chrono::seconds(2));

        ScopedDuration<void(*)(double, const string&)> sf (
            "LambdaTest",
            [](double seconds, const string& tag) {
                cout << tag << " in " << seconds << " seconds" <<endl;
            });

        this_thread::sleep_for(chrono::seconds(2));
    }

    for (auto x : ScopedDurationLoggerData::recordedDurations)
        cout << x.first << " took " << x.second[0] << " seconds" << endl;
}
