#ifndef SearchableStack_HPP
#define SearchableStack_HPP

#include <set>
#include <list>
#include <exception>

/**
 * @brief SearchableStack - A stack which can be efficiently searched for any value. 
 */
template <class T> 
class SearchableStack 
{ 
public: 

    SearchableStack& operator=(const SearchableStack& other);

    void push(const T& t); // O(log n) 
    void pop(); // O(log n) 
    bool contains(const T& t) const; // O(log n) 
    const T& top() const; // O(1) 

    class Empty : public std::exception {};

private: 
    std::multiset<T> set_impl; 
    std::list<typename std::multiset<T>::iterator> list_impl; 
}; 
//--------------------------------------------------------------------------------
/**
 * Offers the Strong Guarantee
 */
template <class T>
SearchableStack<T>&  SearchableStack<T>::operator=(const SearchableStack& other)
{
    if (this != &other)
    {
        // This might have a better place in SearchableStack::swap or free standing swap overload
        // Just use a temporary of your own type, ans swap that one with this
       
        std::multiset<T> tmp; 
        std::list<typename std::multiset<T>::iterator> tmpl;

        for (auto x : other.list_impl)
        {
            tmpl.push_back(tmp.insert(*x));
        }

        // swap never throws, so if this line is reached we're Strong!
        list_impl.swap(tmpl);      
        set_impl.swap(tmp); 
    }
    return *this;
}
//--------------------------------------------------------------------------------
/**
 * push offers the Strong Guarantee
 */
template <class T>
void SearchableStack<T>::push(const T& t)
{
    typename std::multiset<T>::iterator i = set_impl.insert(t);
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
//--------------------------------------------------------------------------------
/**
 * pop offers the Strong Guarantee
 */
template <class T>
void SearchableStack<T>::pop()
{
    if (list_impl.empty()) // NoThrow
        throw Empty();

    typename std::multiset<T>::iterator i = list_impl.back(); // NoThrow
    set_impl.erase(i); // No exceptions if Compare object doesn't throw
    list_impl.pop_back(); // NoThrow
}
//--------------------------------------------------------------------------------
/**
 * contains offers the Strong Guarantee
 * because find offers the Strong Guarantee 
 */
template <class T>
bool SearchableStack<T>::contains(const T& t) const
{
    return set_impl.find(t) != set_impl.end();
}
//--------------------------------------------------------------------------------
/**
 * top offers the Strong Guarantee
 */
template <class T>
const T& SearchableStack<T>::top() const
{
    if (list_impl.empty())
        throw Empty();

    return *(list_impl.back());
}
//--------------------------------------------------------------------------------

#endif // SearchableStack_HPP
