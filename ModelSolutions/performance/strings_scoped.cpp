

#include <iostream>
#include <numeric>
#include <sstream>
#include <functional>

#include <boost/algorithm/string/join.hpp>

#include "ScopedDuration.hpp"

using std::cout;
using std::endl;

using std::string;
string original("Hello");

//--------------------------------------------------------------------------------
void operatorPlus()
{
    ScopedDurationLogger sd("operatorPlus");
    string s;
    for(int i=0; i<100000; ++i)
        s = s + original; 
}
//--------------------------------------------------------------------------------
void operatorPlusEquals()
{
    ScopedDurationLogger sd("operatorPlusEquals");
    string s;
    //size_t cap = s.capacity();

    for(int i=0; i<100000; ++i)
    {
        s += original;    
        
        //if (cap!=s.capacity()) cout << (cap = s.capacity()) << endl;
    }
}
//--------------------------------------------------------------------------------
void boostJoin()
{
    using boost::algorithm::join;
    using std::vector;

    ScopedDurationLogger sd("boostJoin");
    vector<string> strings; // No preallocation
    for(int i=0; i<100000; ++i)
        strings.push_back(original);    
    auto s = join(strings, "");
}
//--------------------------------------------------------------------------------
void boostJoinPreallocate()
{
    using boost::algorithm::join;
    using std::vector;

    ScopedDurationLogger sd("boostJoinPreallocate");
    vector<string> strings; 
    strings.reserve(100000);  // Preallocation!!
    for(int i=0; i<100000; ++i)
        strings.push_back(original);    
    auto s = join(strings, "");
}
//--------------------------------------------------------------------------------
void stringStream()
{
    using std::ostringstream;

    ScopedDurationLogger sd("stringStream");
    ostringstream oss;
    for(int i=0; i<100000; ++i)
        oss << original;

    string s = oss.str();
}
//--------------------------------------------------------------------------------
template<class T>
void printTimings(T times, const char* name, bool verbose=false)
{
    auto it = times.find(name);
    auto average = std::accumulate(begin(it->second), end(it->second), 0.0) / it->second.size();
    cout << name <<" takes on average: " << average << " seconds" <<endl;  

    int i=0;
    if (verbose)
        for (auto x : times[name])
            cout << i++ << ": " << x << " seconds" <<endl; 
}
//--------------------------------------------------------------------------------
auto make_durationlogger(const string& tag)
{
    return ScopedDuration<void(*)(double,const string&)>(tag, [](double seconds, const string& tag)
                                                          { 
                                                              cout << "Duration for " << tag << " :" << seconds << endl;
                                                          });
}
//--------------------------------------------------------------------------------
int main()
{
    using std::map;
    using std::vector;

    // To demo other possibilities of ScopedDurationLogger
    // Using a function functor, demoing decltype
    std::function<void(double,const string&)> logf= [](double seconds, const string& tag){ cout << "Duration for " << tag << " :" << seconds << endl; };
    ScopedDuration<decltype(logf)> sd("Main", logf);

    // Using a lambda as a function pointer
    ScopedDuration<void(*)(double,const string&)> sf("Main2", [](double seconds, const string& tag)
                                                      { 
                                                          cout << "Duration for " << tag << " :" << seconds << endl;
                                                      });
    
    // Using another function to produce a ScopedDurationLogger object coupled to a logger function
    auto sm = make_durationlogger("Main3"); // Rely on RVO to eliminate temporaries

    for (int i=0; i<5; ++i)
    {
        operatorPlus();
        operatorPlusEquals();
        boostJoin();
        boostJoinPreallocate();
        stringStream();
    }

    // Refactor into ScopedDurationLoggerData::PrintResults() taking a print functor/functionptr?
    printTimings(ScopedDurationLoggerData::recordedDurations, "operatorPlusEquals");
    printTimings(ScopedDurationLoggerData::recordedDurations, "operatorPlus");
    printTimings(ScopedDurationLoggerData::recordedDurations, "boostJoin");
    printTimings(ScopedDurationLoggerData::recordedDurations, "boostJoinPreallocate");
    printTimings(ScopedDurationLoggerData::recordedDurations, "stringStream");

}
//--------------------------------------------------------------------------------
