/*
 * References:
 *   [1] http://www.boost.org/community/exception_safety.html
 */

#ifndef SEARCHABLE_STACK
#define SEARCHABLE_STACK

// TODO: eigen oplossing was verkeerd, fix it!

#include <algorithm>
#include <iterator>
#include <list>
#include <set>

template <class T>
class SearchableStack
{
public:
    void push(const T& t);
    void pop();
    bool contains(const T& t) const;
    const T& top() const;
private:
    std::multiset<T> set_impl;

    //list bevat iterators naar...
    //std::list<typename std::multiset<T>::const_iterator> list_impl;  // HIER OOK ANDERS!
    std::list<decltype(set_impl.begin())> list_impl;
};

template <class T>
void SearchableStack<T>::push(const T& t)
{
    auto i = set_impl.insert(t);
    try
    {
        list_impl.push_back(i);
    }
    catch(...)
    {
        set_impl.erase(i);
        throw;
    }
}

template <class T>
void SearchableStack<T>::pop()
{
    // DIT IS VERKEERD!  De list wordt gebruikt om de volgorde te bepalen,
    // de set gewoon om de elementen te hebben.
    auto i = set_impl.erase(std::prev(set_impl.end())); // no exceptions

    if (!list_impl.empty()) {  // noexcept specification
        list_impl.pop_back();  // no exceptions
    }
}

template <class T>
bool SearchableStack<T>::contains(const T& t) const
{
    // VERKEERD! In de ene zitten iterators, maar in de andere zitten de echte elementen!
    
    auto search_set_it = set_impl.find(t);
    auto search_list_it = std::find(list_impl.begin(), list_impl.end(), t);

    return ( (search_set_it != std::end(set_impl.end()))
             && (search_list_it != std::end(list_impl)) );
}


#endif  // SEARCHABLE_STACK
