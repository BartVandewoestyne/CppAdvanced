
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

//--------------------------------------------------------------------------------

/**
 * Easily implemented tokenizer function
 *
 * make CXXFLAGS=-std=c++1y tokfunc
 *
 * Note on locale:
 * Using anything other than whitespace as separator (using peek/ignore), works out of the box for int and others, 
 * because those separators usually don't belong to the number ...
 * They do belong to strings, only whitespace is not considered part of string
 * So a change of locale would be required, which is beyond the scope of this course
 *
 * Note on move: standard: 17.6.5.15 [lib.types.movedfrom]
 * " 
 *   Objects of types defined in the C++ standard library may be moved from (12.8). 
 *   Move operations may be explicitly specified or implicitly generated. 
 *   Unless otherwise specified, such moved-from objects shall be placed in a valid but unspecified state.
 * "
 * So I think what I do with push_back(move) together with ss >> t is legal
 *
 */

//--------------------------------------------------------------------------------
auto tokenize(const string& s) {
    vector<string> vs;
    stringstream ss(s);
    string t;
    while ( ss >> t ) {
        vs.push_back(std::move(t));  // See note on move

        // vs.emplace_back("");  // If std::move wouldn't work, still pretty performant
        // vs.back().swap(t);

        // if (ss.peek() == ',')   // see note on locale
        //     ss.ignore();
    }
    return vs;
}
//--------------------------------------------------------------------------------
/**
 * No-stream tokenizer.
 * 2nd exercise.
 */
auto tokenize2(const string& s) {
    vector<string> tokens;

    // size_t from=0, to = s.find_first_of(" ,;:", from);
    // do
    // {
    //     //cout << from << "-" << to << endl;
    //     tokens.push_back(string(s,from,to-from));
    //     from = to+1;
    // }
    // while(string::npos != (to = s.find_first_of(" ,;:", from)));
    
    size_t from=0, to = 0;
    while (string::npos != (to = s.find_first_of(" ,;:", from)))
    {
        tokens.push_back(string(s,from,to-from));
        from = to+1;
    }

    if (from != s.size())
        tokens.push_back(string(s,from, s.size()-from));

    return tokens;
}
//--------------------------------------------------------------------------------
int main()
{
    string s("1 2 3 4 5 6");   // see note on locale
    auto tokens = tokenize(s);
    
    for (auto x : tokens)
        cout << "= " << x << endl;

    // No-stream tokenizer
    string s2("1 2 42,66;77:88:");
    auto tokens2 = tokenize2(s2);
    cout << "---" << endl;
    for (auto x : tokens2)
        cout << "= " << x << endl;
    
}
//--------------------------------------------------------------------------------
