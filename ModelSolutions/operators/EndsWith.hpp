#ifndef EndsWith_hpp
#define EndsWith_hpp

#include <string>
#include <algorithm>

/**
 * @brief Functor to check if a string ends with a preset value
 */
class EndsWith
{
public:
    EndsWith(const std::string& end) :
        _end(end){}

    inline bool operator()(const std::string& s) const {
        if (s.length() < _end.length() 
            or (_end.length()==0 && s.length()!=0 ))
            return false;

        return std::equal(s.crbegin(), s.crbegin() + _end.length(),
                          _end.crbegin(), _end.crbegin() + _end.length());
    }
    
    typedef std::string argument_type;

private:
    const std::string _end;
};

#endif // EnswWith_hpp
