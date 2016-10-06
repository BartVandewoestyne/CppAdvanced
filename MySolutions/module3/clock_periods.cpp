#include <chrono>
#include <iostream>

int main()
{
  { 
    std::chrono::system_clock::period p;
    std::cout << p.num << '/' << p.den << std::endl;
  }
  {
    std::chrono::steady_clock::period p;
    std::cout << p.num << '/' << p.den << std::endl;
  }
  {
    std::chrono::high_resolution_clock::period p;
    std::cout << p.num << '/' << p.den << std::endl;
  }
}
