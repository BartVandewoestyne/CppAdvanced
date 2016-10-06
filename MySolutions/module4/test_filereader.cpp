#include "TextFileReader.h"

#include <iostream>
#include <string>

auto readlines(const std::string& path) {
    return TextFileReader(path);
}

int main()
{
    for (auto x : readlines("testfile.txt"))
    {
        std::cout << x << std::endl;
    }
}
