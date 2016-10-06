#include <algorithm>
#include <array>
#include <iostream>

template<typename T>
void print(T& a)
{
    for (const auto& e : a)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}

template<typename T>
T clip(const T& n, const T& lower, const T& upper) {
  return std::max(lower, std::min(n, upper));
}


// Just for the fun of it, writing a template function that transforms it.
template<typename T>
T transform(const T& a)
{
    T b;

    std::transform(a.begin(), a.end(), b.begin(),
                  [](typename T::value_type x) {
                      return clip(x, 0, 100);
                  });

    return b;
}

int main()
{
    std::array<int, 6> a = { 10, -10, -100, 100, -200, 200 };
    std::array<int, 6>::value_type x;


    std::cout << "Original array:" << std::endl;
    print(a);

    // Method 1:
    //std::transform(a.begin(), a.end(), a.begin(),
    //      [](int x){
    //          return clip(x, 0, 100);
    //      });
    //
    
    // Method 2:
    std::array<int, 6> b = transform(a);

    std::cout << "Transformed array:" << std::endl;
    print(b);
}
