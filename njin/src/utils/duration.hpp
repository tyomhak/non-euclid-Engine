#include <chrono>

#include "logging.hpp"

namespace njin
{

class DurationLogger
{
using clock = std::chrono::steady_clock;

public:
    DurationLogger(const std::string& message)
    : _start(now())
    , _message(message)
    {}

    ~DurationLogger()
    {
        auto end = now();
        auto duration = end - _start;
        auto durationTime = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        Logger::Log(_message + "{}ms", durationTime);
    }


private:
    static auto now() -> clock::time_point { return clock::now(); }

private:
    clock::time_point _start;
    std::string _message{};
};


};