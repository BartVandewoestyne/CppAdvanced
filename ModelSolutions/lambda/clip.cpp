

#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;


int main()
{
    vector<int> numbers {-5, -42, 42, 101, 666, 888, 66};

    for (auto x : numbers)
        cout << x << ",";
    cout << endl;

    transform(begin(numbers), end(numbers), begin(numbers),
              [](int x) {
                  if (x < 0)
                      return 0;
                  else if (x > 100)
                      return 100;
                  else
                      return x;
              });

    for (auto x : numbers)
        cout << x << ",";
    cout << endl;
    
}
