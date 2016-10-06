#include <iostream>
#include <string>
#include <utility>

class Foo {
public:
    const std::string s = "Foo";

    Foo()
    {
        std::cout << "Foo()" << std::endl;
    }

    Foo(Foo&& f) noexcept :
      s(std::move(f.s))
    {
        std::cout << "Foo(Foo&&)" << std::endl;
    }
};

int main()
{
   Foo f_orig;
   std::cout << "f_orig.s = " << f_orig.s << std::endl;

   Foo f_new(std::move(f_orig));
   std::cout << "f_orig.s = " << f_orig.s << std::endl;
   std::cout << "f_new.s = " << f_new.s << std::endl;
}
