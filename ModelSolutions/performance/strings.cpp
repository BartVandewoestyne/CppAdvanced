

#include <string>
#include <chrono>
#include <iostream>
#include <map>
#include <vector>
#include <numeric>
#include <sstream>

#include <boost/algorithm/string/join.hpp>

#define NUMLOOPS 100000

using std::string;
string original("Hello");

//--------------------------------------------------------------------------------
void operatorPlus()
{
    string s;
    for(int i=0; i<NUMLOOPS; ++i)
        s = s + original; 
}
//--------------------------------------------------------------------------------
void operatorPlusEquals()
{
    string s;
    for(int i=0; i<NUMLOOPS; ++i)
        s += original;    
}
//--------------------------------------------------------------------------------
void boostJoin()
{
    using boost::algorithm::join;
    using std::vector;
    vector<string> strings; // No preallocation
    for(int i=0; i<NUMLOOPS; ++i)
        strings.push_back(original);    
    auto s = join(strings, "");
}
//--------------------------------------------------------------------------------
void boostJoinPreallocate()
{
    using boost::algorithm::join;
    using std::vector;
    vector<string> strings; // No preallocation
    strings.reserve(NUMLOOPS);
    for(int i=0; i<NUMLOOPS; ++i)
        strings.push_back(original);    
    auto s = join(strings, "");
}
//--------------------------------------------------------------------------------
void stringStream()
{
    using std::ostringstream;
    ostringstream oss;
    for(int i=0; i<NUMLOOPS; ++i)
        oss << original;

    string s = oss.str();
}
//--------------------------------------------------------------------------------
/**
 * Function to time execution of void(void) functions
 * Using C++14 automatic return type deduction
 */
template<typename Function>
auto timeIt(Function t)
{
    using namespace std::chrono;
    //time_point<system_clock> start, end; // Why bother! Use auto

    auto start = system_clock::now();
    t();
    auto end = system_clock::now();
    
    duration<double> elapsed_seconds = end-start;
    return elapsed_seconds.count();
}
//--------------------------------------------------------------------------------
template<class T>
void printTimings(T times, const char* name, bool verbose=false)
{
    using std::cout;
    using std::endl;

    auto it = times.find(name);
    auto average = std::accumulate(begin(it->second), end(it->second), 0.0) / it->second.size();
    cout << name <<" takes on average: " << average << " seconds" <<endl;  

    int i=0;
    if (verbose)
        for (auto x : times[name])
            cout << i++ << ": " << x << " seconds" <<endl; 
}
//--------------------------------------------------------------------------------
int main()
{
    using std::map;
    using std::vector;
    
    map<string,vector<double>> times;
    // times["operatorPlus"].reserve(10);
    // times["operatorPlusEquals"].reserve(10);
    // times["boostJoin"].reserve(10);
    // times["boostJoin"].reserve(10);

    for (int i=0; i<50; ++i)
    {
        times["operatorPlus"].push_back(timeIt(&operatorPlus));
        times["operatorPlusEquals"].push_back(timeIt(&operatorPlusEquals));
        times["boostJoin"].push_back(timeIt(&boostJoin));
        times["boostJoinPreallocate"].push_back(timeIt(&boostJoinPreallocate));
        times["stringStream"].push_back(timeIt(&stringStream));
    }

    printTimings(times, "operatorPlusEquals");
    printTimings(times, "operatorPlus");
    printTimings(times, "boostJoin");
    printTimings(times, "boostJoinPreallocate");
    printTimings(times, "stringStream");
}
//--------------------------------------------------------------------------------
