
/**
 * make CXXFLAGS=-std=c++1y strings2tuple
 */

#include <vector>
#include <string>
#include <tuple>
#include <sstream>
#include <iostream>

using namespace std;
//--------------------------------------------------------------------------------

/**
 * See tupletok.cpp for extra info
 *
 * Different scenario's were possible here
 * Including one where you don't work with iterators, but with a subslice
 * However this would require pop_front, which is not in vector because of sloooow
 * Which is also an indication we shouldn't abuse erase to do this
 *
 * So iterators!, pretty performant, as I'm passing them by value
 * The bulk of the work/time will be in stringstream
 *
 */

//--------------------------------------------------------------------------------


template<class... T> 
struct strings {
    static tuple<T...> totuple(vector<string>::const_iterator& v);
};


template<>
struct strings<> {

    static auto totuple(vector<string>::const_iterator& v) {
        return make_tuple<>();
    }
};

template<class T, class... Other>
struct strings<T, Other...> {

    static auto totuple(vector<string>::const_iterator& v) {
        T x;
        stringstream ss(*v);
        ss >> x;
        return tuple_cat(tie(x), strings<Other...>::totuple(++v));
    }
};


template<class...T>
auto strings2tuple(const vector<string>& v)  
{
    auto it = v.cbegin();
    return strings<T...>::totuple(it);
}
//--------------------------------------------------------------------------------
int main()
{
    vector<string> v {"1","42","3.14","2.71","Foo"};

    auto x = strings2tuple<int,int,double,double,string>(v);
    
    int a,b; double c,d; string e;
    tie(a,b,c,d,e) = x;
    
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;
    cout << d << endl;
    cout << e << endl;
    
}
//--------------------------------------------------------------------------------
