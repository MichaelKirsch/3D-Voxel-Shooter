

#include "StopWatch.h"

StopWatch::StopWatch() {
    start = std::chrono::steady_clock::now();
}

int StopWatch::stop(StopWatch::timer_mode mode) {
    std::chrono::_V2::steady_clock::time_point end = std::chrono::steady_clock::now();
    switch (mode)
    {
        case timer_mode::micro :
            return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        case timer_mode::milli :
            return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        default:
            return std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
    }

}
