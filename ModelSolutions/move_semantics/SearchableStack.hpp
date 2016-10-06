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
    SearchableStack();
    SearchableStack(SearchableStack&& other);

    SearchableStack& operator=(const SearchableStack& other) ;
    SearchableStack& operator=(SearchableStack&& other) noexcept(noexcept(std::list<typename std::set<T>::iterator>::swap));

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
SearchableStack<T>::SearchableStack() :
    set_impl(),
    list_impl()
{}
//--------------------------------------------------------------------------------
/**
 * What about exception guarantee for this one?
 * std container move constructors can throw, but offer strong guarantee
 *
 * We can't offer the Strong Guarantee, because say we're moving the list in a try/catch:
 * During the catch, we want to restore other's set, but if it in turn throws, we're not Strong
 * We're in need of a NoThrow/NoFail to make our MoveCtor Strong or even NoThrow/NoFail/noexcept
 *
 * This means that a collection of SearchableStacks (*why?) won't be movable because of move_if_noexcept
 *
 * Want the strong for this one? (Not for move assignment) Use copy
 *
 * Implicitly we're offering the Basic Guarantee here,
 * All resources are managed by the containers themselves
 */
/*
template <class T>
SearchableStack<T>::SearchableStack(SearchableStack&& other) :
    set_impl(std::move(other.set_impl)),
    list_impl(std::move(other.list_impl))
{}
*/
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

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
 * At least the Strong Guarantee, possibly noexcept
 */
template <class T>
SearchableStack<T>& SearchableStack<T>::operator=(SearchableStack<T>&& other) noexcept(noexcept(std::list<typename std::set<T>::iterator>::swap))
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
       
        std::set<T> tmp; 
        std::list<typename std::set<T>::iterator> tmpl;

        for (auto x : other.list_impl)
            tmpl.push_back(tmp.insert(*x).first);

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
    typename std::set<T>::iterator i = set_impl.insert(t).first; // Since C++11 insert returns a std::pair<iterator,bool>
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

    typename std::set<T>::iterator i = list_impl.back(); // NoThrow
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
