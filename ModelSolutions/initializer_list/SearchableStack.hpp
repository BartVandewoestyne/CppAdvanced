#ifndef SearchableStack_HPP
#define SearchableStack_HPP

#include <set>
#include <list>
#include <exception>
#include <initializer_list>

/**
 * @brief SearchableStack - A stack which can be efficiently searched for any value. 
 *
 * Modernized some pieces, leaving the old in comments
 */
template <class T> 
class SearchableStack 
{ 
private: 
    std::multiset<T> set_impl; 
    //std::list<typename std::multiset<T>::iterator> list_impl; 
    std::list<decltype(set_impl.begin())> list_impl; 

public: 
    SearchableStack();
    SearchableStack(SearchableStack&& other);
    SearchableStack(std::initializer_list<T> init);

    SearchableStack& operator=(const SearchableStack& other) ;
// SearchableStack& operator=(SearchableStack&& other) noexcept(noexcept(std::list<typename std::set<T>::iterator>::swap));
    SearchableStack& operator=(SearchableStack&& other) noexcept(noexcept(decltype(list_impl)::swap));

    void push(const T& t); // O(log n) 
    void pop(); // O(log n) 
    bool contains(const T& t) const; // O(log n) 
    const T& top() const; // O(1) 

    class Empty : public std::exception {};


}; 
//--------------------------------------------------------------------------------
template <class T>
SearchableStack<T>::SearchableStack() :
    set_impl(),
    list_impl()
{}
//--------------------------------------------------------------------------------
/**
 * Strong Guarantee
 * Not NoThrow/NoFail/noexcept because constructors of set/list can throw
 */
template <class T>
SearchableStack<T>::SearchableStack(SearchableStack&& other) :
    set_impl(),  // Explicit default construction, didn't have to write an initializer list here
    list_impl()
{
     set_impl.swap(other.set_impl);
     list_impl.swap(other.list_impl);
}
//--------------------------------------------------------------------------------
/**
 * Strong guarantee: Object will have never existed if something goes wrong
 */
template <class T>
SearchableStack<T>::SearchableStack(std::initializer_list<T> init) :
    set_impl(),
    list_impl()
{
    for (auto x : init)
        list_impl.push_back(set_impl.insert(x));
}
//--------------------------------------------------------------------------------
/**
 * At least the Strong Guarantee, possibly noexcept
 */
template <class T>
//SearchableStack<T>& SearchableStack<T>::operator=(SearchableStack<T>&& other) noexcept(noexcept(std::list<typename std::multiset<T>::iterator>::swap))
SearchableStack<T>& SearchableStack<T>::operator=(SearchableStack<T>&& other) noexcept(noexcept(decltype(list_impl)::swap))
{
    if (this != &other)
    {
        set_impl.swap(other.set_impl);
        list_impl.swap(other.list_impl);
    }
    return *this;
}
//--------------------------------------------------------------------------------
/**
 * Offers the Strong Guarantee
 * NoFail/NoThrow not possible because constructors, insert and push back can throw
 */
template <class T>
SearchableStack<T>& SearchableStack<T>::operator=(const SearchableStack& other)
{
    if (this != &other)
    {
        // This might have a better place in SearchableStack::swap or free standing swap overload
        // Just use a temporary of your own type, ans swap that one with this
       
        //std::multiset<T> tmp; 
        decltype(set_impl) tmp; 
        //std::list<typename std::multiset<T>::iterator> tmpl;
        decltype(list_impl) tmpl;

        for (auto x : other.list_impl)
            tmpl.push_back(tmp.insert(*x));

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
//--------------------------------------------------------------------------------
/**
 * pop offers the Strong Guarantee
 */
template <class T>
void SearchableStack<T>::pop()
{
    if (list_impl.empty()) // NoThrow
        throw Empty();

    auto i = list_impl.back(); // NoThrow
    set_impl.erase(i); // No exceptions if Compare object doesn't throw
    list_impl.pop_back(); // NoThrow
}
//--------------------------------------------------------------------------------
/**
 * contains offers at least the String Guarantee
 * Perhaps even the NoThrow/NoFail, but set.find() documentation lacks information on exception safety
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
