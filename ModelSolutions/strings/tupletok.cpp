
/**
 * make CXXFLAGS=-std=c++1y tupletok
 */

#include <tuple>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;
//--------------------------------------------------------------------------------

/**
 * Tokenizer that outputs a tuple<choice...> of your choice
 *
 * Originally ment to use only a recursive template function ...
 * After an hour I arrived at the following.
 * 
 * Wouldn't know how to begin writing the exercise assignment,
 * as we didn't cover template specialization or variadic templates
 *
 * So it's in here as a sort-of example
 * Really simple implementation if you know C++
 * Everyone (*) probably understand this
 * 
 * Sadly ... takes quite a bit more C++ chops to write ...
 */

//--------------------------------------------------------------------------------

template<typename ... Other> struct Tokenizer;

template<>
struct Tokenizer<>
{
    static auto toktok(stringstream&& s) {
        return make_tuple<>();
    }
};

template<class T, class... Other>
struct Tokenizer<T, Other...>
{
    static auto toktok(stringstream&& s) {
        T x;
        s >> x;
        return tuple_cat(std::tie(x), Tokenizer<Other...>::toktok(std::move(s)));
    }
};
//--------------------------------------------------------------------------------
template<class... args>
auto toktok(const string& s) {  // Accepting temporaries
    return Tokenizer<args...>::toktok(stringstream(s));
}
//--------------------------------------------------------------------------------
int main()
{
    string s("1 3.14 2.71 Foo Faa");

    // Expecting a tuple<int, double, double, string>
    // The number of template types exclude "Faa" from the tuple

    auto x = toktok<int, double, double, string>(s);

    int a; double b; double c; string d;
    std::tie(a,b,c,d) = x;

    cout << a << endl;
    cout << b << endl;
    cout << c << endl;
    cout << d << endl;
    
}
//--------------------------------------------------------------------------------
