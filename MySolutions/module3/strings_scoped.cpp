/*!
 * Optimization also plays a role here!
 */ 

#include "ScopedDurationLogger.h"

#include <sstream>
#include <string>

std::string original("Hello");

const int NB_INSTANCES = 100000;

void operatorPlus()
{
    ScopedDurationLogger sd("OperatorPlus");
    std::string s;
    for (int i = 0; i < NB_INSTANCES; ++i)
    {
        s = s + original;
    }
}

void operatorPlusEquals()
{
    ScopedDurationLogger sd("OperatorPlusEquals");
    std::string s;
    for (int i = 0; i < NB_INSTANCES; ++i)
    {
        s += original;
    }
}

void appendIt()
{
    ScopedDurationLogger sd("AppendIt");
    std::string s;
    for (int i = 0; i < NB_INSTANCES; ++i)
    {
        s += original;
    }
}

void boostJoin()
{
}

void oStringStream()
{
    ScopedDurationLogger sd("ostringstream");
    std::string s;
    std::ostringstream oss(s);
    for (int i = 0; i < NB_INSTANCES; ++i)
    {
        oss << original;
    }
}

int main()
{
    operatorPlus();
    operatorPlusEquals();
    oStringStream();
    appendIt();
}
