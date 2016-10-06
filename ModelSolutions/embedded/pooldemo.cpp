
#include <iostream>
#include <vector>
#include <boost/shared_ptr.hpp>

#include "StaticMemoryPool.hpp"

using std::cout;
using std::endl;
using std::vector;
using boost::shared_ptr;

//--------------------------------------------------------------------------------
struct Foo
{
    int d[5];

public: 
    Foo() {
        cout << "Foo::Foo()" << endl;
    };

    ~Foo() {
        cout << "Foo::~Foo()" << endl;
    };

    void* operator new(size_t size);
    void operator delete(void*, size_t size);
};
//--------------------------------------------------------------------------------

// Normally declare extern, define in Foo.cpp
static StaticMemoryPool<Foo, 10> pool;

//--------------------------------------------------------------------------------
void* Foo::operator new(size_t size){
    return pool.allocate();
}
//--------------------------------------------------------------------------------
void Foo::operator delete(void* p, size_t size){
    return pool.deallocate(static_cast<Foo*>(p));
}
//--------------------------------------------------------------------------------


// C++98 ...
int main(int argc, char* argv[])
{
    cout << "Main" << endl;
    
    {
        // Just use Foo objects like you're used to
        // You don't notice them not comming from the heap
        vector<shared_ptr<Foo> > foos;
        for (int i=0; i<10; ++i)
            foos.push_back(shared_ptr<Foo>(new Foo));

        if (argc > 1)
            // trigger the assert
            foos.push_back(shared_ptr<Foo>(new Foo));
    }

    cout << "Clear" << endl;
};

