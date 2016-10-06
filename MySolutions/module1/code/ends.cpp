/*
 * Notes:
 *
 *   - deriving from std::unary_function is deprecated since C++11
 *   - The unary predicate type must define a member type, argument_type, that is convertible to
 *     the predicate's parameter type.
 *
 * References:
 *
 *   [1] http://www.cplusplus.com/reference/functional/not1/
 *   [2] http://en.cppreference.com/w/cpp/utility/functional/not1
 *
 */

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>


//class EndsWith : std::unary_function<const std::string&, bool> // deprecated since C++11
class EndsWith
{
public:
    EndsWith(const std::string& s) : _expected(s) {}

    // Remark: note that you should not forget the const here!
    bool operator()(const std::string& s) const {

        if (_expected.length() <= s.length()) {
            return s.compare(s.length() - _expected.length(), _expected.length(), _expected) == 0;
        } else {
            return false;
        }

    }

    typedef const std::string& argument_type;

private:
    const std::string _expected;
};


namespace tass {

    template<class Predicate>
    class unary_negate {
    public:
        explicit unary_negate(const Predicate& p) : _p(p) {}
    
        bool operator()(const typename Predicate::argument_type& arg) {
            return !_p(arg);
        }
    private:
        Predicate _p;
    };

    // TODO: continue this
    // template<class Predicate>
    // tass::unary_negate<Predicate> not1(const Predicate& pred);

}


template <typename T>
void print(const std::vector<T>& vec)
{
    for (const auto& e : vec)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}


int main()
{
    const std::vector<std::string> v { "boo", "foo", "zoo", "zo", "bar", "fubar" };

    std::vector<std::string> strings = v;
    std::cout << "Original vector:" << std::endl;
    print(strings);

    std::cout << "After erasing everything that ends with oo" << std::endl;
    strings.erase(std::remove_if(begin(strings), end(strings), EndsWith("oo")),
                  end(strings));
    print(strings);

    strings = v;
    std::cout << "After erasing everything that NOT ends with oo" << std::endl;
    strings.erase(std::remove_if(begin(strings), end(strings), std::not1(EndsWith("oo"))),
                  end(strings));
    print(strings);

    strings = v;
    std::cout << "After erasing everything that NOT ends with oo" << std::endl;
    strings.erase(std::remove_if(begin(strings), end(strings), std::unary_negate<EndsWith>(EndsWith("oo"))),
                  end(strings));
    print(strings);

    strings = v;
    std::cout << "After erasing everything that NOT ends with oo" << std::endl;
    strings.erase(std::remove_if(begin(strings), end(strings), tass::unary_negate<EndsWith>(EndsWith("oo"))),
                  end(strings));
    print(strings);
}
