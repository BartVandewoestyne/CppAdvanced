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
    void push(const T& t); // O(log n) 
    void pop(); // O(log n) 
    bool contains(const T& t) const; // O(log n) 
    const T& top() const; // O(1) 

    class Empty : public std::exception {};

private: 
    std::set<T> set_impl; 
    std::list<typename std::set<T>::iterator> list_impl; 
}; 
//--------------------------------------------------------------------------------
template <class T>
void SearchableStack<T>::push(const T& t)
{
    typename std::set<T>::iterator i = set_impl.insert(t);
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
template <class T>
void SearchableStack<T>::pop()
{

}
//--------------------------------------------------------------------------------
template <class T>
bool SearchableStack<T>::contains() const
{

}
//--------------------------------------------------------------------------------
template <class T>
const T& SearchableStack<T>::top() const
{

}
//--------------------------------------------------------------------------------

#endif // SearchableStack_HPP
