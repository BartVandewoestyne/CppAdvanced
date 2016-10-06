#ifndef ScopedDuration_HPP
#define ScopedDuration_HPP

#include <chrono>
#include <string>
#include <map>
#include <vector>


/**
 * @brief Very dump functor to keep track of submitted durations for a given tag
 */
struct ScopedDurationLoggerData
{
    static std::map<std::string, std::vector<double>> recordedDurations;

    void operator()(double seconds, const std::string& tag){
        recordedDurations[tag].push_back(seconds);
    }
};

// Hack, better put this in it's own cpp file
std::map<std::string, std::vector<double>> ScopedDurationLoggerData::recordedDurations;

template<typename SubmitFunction>
class ScopedDuration
{
public:
    ScopedDuration(const std::string& tag, SubmitFunction f=SubmitFunction()) :
        tag(tag),
        start(std::chrono::system_clock::now()),
        function(f){}

    ~ScopedDuration(){
        std::chrono::duration<double> elapsed_seconds = 
            std::chrono::system_clock::now()-start;

        function(elapsed_seconds.count(), tag);
    }
    
private:    
    std::string tag;
    std::chrono::time_point<std::chrono::system_clock> start;
    SubmitFunction function;
};


typedef ScopedDuration<ScopedDurationLoggerData> ScopedDurationLogger;

#endif // ScopedDuration_HPP
