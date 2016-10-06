#include <iostream>
#include <thread>

void foo() {
    std::cout << "Hello Thread" << std::endl;
}

int main()
{
    std::thread t1(foo);
    std::thread t2([](){ std::cout << "Hello Lambda" << std::endl;});
    std::cout << "Hello Main" << std::endl;
    t1.join();
    t2.join();
}
