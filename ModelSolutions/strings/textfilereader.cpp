
/**
 * @brief TextFileReader: a convenience class for dealing with line based files 
 *
 * make CXXFLAGS=-std=c++1y textfilereader
 *
 * using the readlines() wrapper function, a range-for loop can iterate over lines in a text file
 * in a lazy way, only reading the next line from file on iterator increment
 * 
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;
//--------------------------------------------------------------------------------

class TextFileReader
{
public:
    TextFileReader(const string& path) : 
        path(path) {}

    /**
     * @brief inner Iterator in TextFileReader: Does the actual work
     *
     * Inherits from std::iterator<> to be used with std::vector<>
     */
    class Iterator : public iterator<input_iterator_tag, string>
    {
    public:
        friend class TextFileReader;

        Iterator& operator++() { 
            if (!getline(file, line)) {
                file.close(); // no more data, 
                line.erase(); // turn it into end() iterator
            }
            return *this; 
        }

        string& operator*() { return line; }

        bool operator==(const Iterator& i) {  
            return file.is_open() == i.file.is_open()
                && line == i.line; // consider this equal, not waterproof!!!
        }

        bool operator!=(const Iterator& i) { return !operator==(i); }
        
    private:
        Iterator() : file(), line() {}
        Iterator(const string& path) : file(path), line() {
            operator++(); // load the first line
        }
        ifstream file;
        string line;
    };

    auto begin() { return Iterator(path); }
    auto end() { return Iterator(); }

private:
    string path;
};
//--------------------------------------------------------------------------------
auto readlines(const string& path) 
{
    return TextFileReader(path);
}
//--------------------------------------------------------------------------------
int main()
{
    for (auto x : readlines("testfile.txt"))
        cout << x << endl;

    auto lines = readlines("testfile.txt");
    vector<string> t(lines.begin(), lines.end());
    transform(t.begin(), t.end(), t.begin(), 
              [](const string& s){
                  return string("PREFIX ") + s;
              });
    
    for (auto x : t )
        cout << x <<endl;
}
//--------------------------------------------------------------------------------
