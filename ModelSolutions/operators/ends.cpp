
#include <vector>
#include <string>
#include <iostream>
using namespace std;

#include "EndsWith.hpp"


int main()
{
    vector<string> strings { "boo", "foo", "zoo", "zo", "bar", "fubar" };

    for (auto x : strings)
        cout << x << endl;

    cout << endl;

    strings.erase(remove_if(begin(strings), end(strings), EndsWith("oo"))
                  , end(strings));

    for (auto x : strings)
        cout << x << endl;
}
