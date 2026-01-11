#include <chrono>

#include "logging.hpp"

namespace njin
{

class DurationLogger
{
using clock = std::chrono::steady_clock;

public:
    DurationLogger(const std::string& message)
    : _start(clock::now())
    , _message(message)
    {}

    ~DurationLogger()
    {
        auto end = clock::now();
        auto duration = end - _start;
        auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        Logger::Log(_message + "{}ms", duration_ms);
    }

private:
    clock::time_point _start;
    std::string _message{};
};


class Timer
{
using clock = std::chrono::steady_clock;
public:
    Timer() : _start(clock::now()){}

    auto get_ms() const
    {
        auto end = clock::now();
        auto duration = end - _start;
        return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    }

    auto reset()
    {
        _start = clock::now();
    }

private:
    clock::time_point _start;
};


};