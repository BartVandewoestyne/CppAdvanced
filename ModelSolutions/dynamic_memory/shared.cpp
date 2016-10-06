

/**
 * To compile: $ make shared CXXFLAGS=-std=c++11
 */

#include <memory>
#include <iostream>

using namespace std;

class Foo
{
public:
    Foo() {
        cout << "Foo():" << this << endl;
    }

    ~Foo() {
        cout << "~Foo(): " << this << endl;
    }
};


unique_ptr<Foo> unique_wrapper(Foo* p)
{
    cout << "unique_wrapper(): " << p << endl;
    return unique_ptr<Foo>(p);
}

//void foo(unique_ptr<Foo> 

void some_function(unique_ptr<Foo> first, unique_ptr<Foo> second) {
    cout << "some_function()" << endl;
}


int main()
{
    cout << "Main()" << endl;
    {
        cout << "Creating a Foo" << endl;
        auto p = make_shared<Foo>();
        
        cout << "Doing unique stuff" << endl;
        some_function(unique_wrapper(new Foo()), unique_wrapper(new Foo()));

        cout << "Leaving scope" << endl;
    }
    cout << "Leaving main()" << endl;
}
