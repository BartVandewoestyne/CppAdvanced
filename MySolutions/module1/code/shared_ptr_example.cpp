#include <iostream>
#include <memory>

class Foo {
public:
    Foo() { std::cout << "Foo()" << std::endl; }
    ~Foo() { std::cout << "~Foo()" << std::endl; }
};

std::unique_ptr<Foo> unique_wrapper(Foo* pf)
//std::unique_ptr<Foo> unique_wrapper(const Foo* const pf)
{
    std::cout << "unique_wrapper: pf = " << pf << std::endl;

    return std::unique_ptr<Foo>(pf);
    //return std::make_unique<Foo>();
}

void somefunction(const std::unique_ptr<Foo>& p1, const std::unique_ptr<Foo>& p2)
{
    std::cout << "somefunction()" << std::endl;
}

int main()
{
    {
        std::cout << "Exercise 2.1:" << std::endl;
        auto spf = std::make_shared<Foo>();
    }

    {
        std::cout << "Exercise 2.2:" << std::endl;
        somefunction(unique_wrapper(new Foo()),
                     unique_wrapper(new Foo()));
    }
}
