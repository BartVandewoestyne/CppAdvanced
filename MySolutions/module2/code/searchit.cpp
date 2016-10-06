#include "SearchableStack.h"

int main()
{
    SearchableStack<int> s;

    s.push(1);
    s.pop();

    s.push(2);
    s.contains(2);
}
