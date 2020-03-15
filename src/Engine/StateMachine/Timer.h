

#pragma once

class Timer {
public:
    void setTickrate(unsigned int tickrate);
    void setElapsed(float& elapsed);
    bool getState();
    ~Timer()= default;
private:
    unsigned int m_tickrate;
    float m_elapsed, timer;
};



