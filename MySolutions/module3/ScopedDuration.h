#ifndef SCOPED_DURATION
#define SCOPED_DURATION

#include <chrono>
#include <iostream>
#include <string>

template<typename SubmitFunction>
class ScopedDuration
{
public:
    ScopedDuration(const std::string& tag, SubmitFunction f = SubmitFunction())
      : m_tag(tag)
      , m_f(f)
      , m_start(std::chrono::steady_clock::now())
      , m_stop(m_start)
    {
        std::cout << "ScopedDuration()" << std::endl;
    }

    ~ScopedDuration()
    {
         std::cout << "~ScopedDuration()" << std::endl;

         m_stop = std::chrono::steady_clock::now();
         std::chrono::duration<double> elapsed_seconds = m_stop - m_start;

         m_f(elapsed_seconds.count(), m_tag);
    }

private:
    std::string m_tag;
    SubmitFunction m_f;
    std::chrono::time_point<std::chrono::steady_clock> m_start;
    std::chrono::time_point<std::chrono::steady_clock> m_stop;
    
};

#endif  // SCOPED_DURATION
