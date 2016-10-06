#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> tokenize2(const std::string& s_in, const std::string& separator = " ")
{
    std::vector<std::string> result;

    std::string s(s_in);
    std::string tok;
    while (tok != s)
    {
        tok = s.substr(0, s.find_first_of(separator));
        s = s.substr(s.find_first_of(separator) + 1);
        result.push_back(tok);
    }
    return result;
}

std::vector<std::string> tokenize1(const std::string& s)
{
    std::vector<std::string> result;

    std::stringstream ss(s);
    std::string tok;
    while ( ss >> tok)
    {
        result.push_back(tok);
    }

    return result;
}

int main()
{
    std::string s = "Hello world from Bart.";

    std::vector<std::string> res1 = tokenize1(s);
    for (const auto& e : res1)
    {
        std::cout << e << std::endl;
    }

    std::vector<std::string> res2 = tokenize2(s);
    for (const auto& e : res2)
    {
        std::cout << e << std::endl;
    }
}
