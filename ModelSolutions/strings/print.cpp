

/**
 * @brief self named print idiom demo
 *
 * make CXXFLAGS=-std=c++1y print
 */

#include <iostream>
#include <string>
#include <utility>

using namespace std;
//--------------------------------------------------------------------------------

template<class... T>
struct print_helper {
    static void help(const T&... args);
};

// empty specialization, to stop the template recursion
template<>
struct print_helper<> {
    static void help() {
        cout << endl;
    }
};

template<class T, class... OtherTypes>
struct print_helper<T, OtherTypes...> {
    static void help(const T& t, const OtherTypes&... o) {
        cout << t << " ";
        print_helper<OtherTypes...>::help(o...);
    }
};

//--------------------------------------------------------------------------------
template<class... T>
void print(const T&... args)
{
    print_helper<T...>::help(args...);
}
//--------------------------------------------------------------------------------
int main()
{
    int a=1, b=42; string s("Hello");
    double p=3.14;
    auto x("Tass");

    print(a,b,s,p,s,s,p,s,x);
}
//--------------------------------------------------------------------------------
