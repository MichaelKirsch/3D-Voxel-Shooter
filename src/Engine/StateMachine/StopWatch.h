

#pragma once
#include <chrono>
class StopWatch {

public:
    enum timer_mode
    {
        seconds,micro,milli
    };
    StopWatch();
    int stop(timer_mode mode=timer_mode::micro);
    ~StopWatch() = default;

private:
    std::chrono::_V2::steady_clock::time_point start;
protected:
};



