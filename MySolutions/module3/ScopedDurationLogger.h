#ifndef SCOPED_DURATION_LOGGER_H
#define SCOPED_DURATION_LOGGER_H

#include <chrono>
#include <iostream>
#include <string>

class ScopedDurationLogger {
public:
    ScopedDurationLogger(const std::string& tag)
      : m_tag(tag)
      , m_start(std::chrono::steady_clock::now())
      , m_stop(m_start)
    {
        std::cout << "ScopedDurationLogger()" << std::endl;
    }

    ~ScopedDurationLogger()
    {
         std::cout << "~ScopedDurationLogger()" << std::endl;

         m_stop = std::chrono::steady_clock::now();
         std::chrono::duration<double> elapsed_seconds = m_stop - m_start;

         std::cout << "Elapsed time (s): " << elapsed_seconds.count() << std::endl;
    }

private:
    std::string m_tag;
    std::chrono::time_point<std::chrono::steady_clock> m_start;
    std::chrono::time_point<std::chrono::steady_clock> m_stop;
};

#endif  // SCOPED_DURATION_LOGGER_H
