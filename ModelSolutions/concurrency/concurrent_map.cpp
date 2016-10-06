

/*
 *  make CXXFLAGS=-std=c++1y concurrent_map && ./concurrent_map
 */

#include <array>
#include <future>
#include <vector>
#include <iterator>
#include <iostream>
#include <thread>
using namespace std;

#include <cstdio>
// --------------------------------------------------------------------------------
template <typename T, typename S>
void concurrent_map(T& items, const S& function) 
{
    auto const nthreads = 4;
    auto elementsPerThread = distance(begin(items), end(items)) / nthreads;
    vector<future<S>> futures;
    futures.reserve(nthreads);

    auto it = begin(items);
    for (int i=0; i<nthreads; ++i, it+=elementsPerThread)
    {
        auto threadrange = make_pair(it, ( i!=nthreads-1 ? it+elementsPerThread : end(items)));
        futures.push_back( async( [threadrange,  &function] {
                    return for_each(threadrange.first, threadrange.second, function); 
                }));
    }

    for (auto& f : futures)
        f.wait();
}
// --------------------------------------------------------------------------------
int main()
{
    vector<int> vals {1,2,3,4,5,6,7,8,9,10};
    
    for (auto x : vals)
        cout << x << endl;

    concurrent_map(vals, [](auto& x){ 
            x+=1; 
        });
    
    for (auto x : vals)
        cout << x << endl;
}
// --------------------------------------------------------------------------------

