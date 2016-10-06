//#define BASIC
//#define ADVANCED
//#define LAMBDA
#define LOGGER_DATA

#if defined(BASIC)
  #include "ScopedDurationLogger.h"
#elif defined(ADVANCED)
  #include "ScopedDuration.h"
#elif defined(LOGGER_DATA)
  #include "ScopedDuration.h"
  #include "ScopedDurationLoggerData.h"
#endif

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

void bar()
{
    std::cout << "bar()" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    //std::this_thread::sleep_for(1s);  // C++14
}

void fubar()
{
    std::cout << "fubar()" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    //std::this_thread::sleep_for(2s);  // C++14
}

int DoRequest()
{
    std::cout << "DoRequest()" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    //std::this_thread::sleep_for(3s);  // C++14
}

void ProcessRequest(int r)
{
    std::cout << "ProcessRequest" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(4));
    //std::this_thread::sleep_for(4s);  // C++14
}

class SubmitFunction {
public:
    void operator() (double seconds, const std::string& tag) const
    {
        std::cout << tag << " took " << seconds << " seconds" << std::endl;
    }
};

void foo()
{
    SubmitFunction f;

#if defined(BASIC)
    ScopedDurationLogger d1("foo");
#elif defined(ADVANCED)
    ScopedDuration<SubmitFunction> d1("foo");
#elif defined(LOGGER_DATA)
    ScopedDuration<ScopedDurationLoggerData> d1("foo-Request");
#elif defined(LAMBDA)
    ScopedDuration<void(*)(double, const std::string&)> sf("SomeUsefullTag",
      [](double seconds, const std::string& tag)
      {
          std::cout << "Duration for " << tag << ": " << seconds << std::endl;
      });
#endif

    bar();
    fubar();

    {

#if defined(BASIC)
        ScopedDurationLogger d2("foo-Request");
#elif defined(ADVANCED)
        ScopedDuration<SubmitFunction> d2("foo-Request");
#elif defined(LOGGER_DATA)
        ScopedDuration<ScopedDurationLoggerData> d2("foo-Request");
#elif defined(LAMBDA)
        ScopedDuration<void(*)(double, const std::string&)> sf("SomeUsefullTag",
          [](double seconds, const std::string& tag)
          {
              std::cout << "Duration for " << tag << ": " << seconds << std::endl;
          });
#endif

        auto r = DoRequest();

    }
}

int main()
{
    foo();
}
