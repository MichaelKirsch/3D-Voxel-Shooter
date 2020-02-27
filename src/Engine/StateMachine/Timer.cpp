

#include "Timer.h"

void Timer::setTickrate(unsigned int tickrate) {
    m_elapsed = 0.f;
    timer = 1.f/tickrate;
}

void Timer::setElapsed(float elapsed) {
    m_elapsed+=elapsed;
}

bool Timer::getState() {
    if(m_elapsed>timer)
    {
        m_elapsed=0.f;
        return true;
    }
    return false;
}
