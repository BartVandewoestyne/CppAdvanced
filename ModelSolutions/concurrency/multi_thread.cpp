

#include <thread>
#include <vector>
#include <iostream>
#include <mutex>
using namespace std;

mutex m;

int main(int argc, char** argv)
{
    vector<thread> threads;
    
    for (int i=0; i<10; ++i)
        threads.emplace_back( thread( [&] (int x){
                    if (argc > 1) 
                    {
                        lock_guard<mutex> lg(m);
                        cout << this_thread::get_id() << " "  << x << endl;
                    }
                    else
                        cout << this_thread::get_id() << endl;
                }, i));

    for (auto& t : threads)
        t.join();
}
