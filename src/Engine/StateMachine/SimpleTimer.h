

#pragma once

class SimpleTimer {
public:
    bool check(float elapsed){
        time+=elapsed;
        if(time>tickrate)
        {
            reset();
            return true;
        }
        return false;
    };
    void reset(){time=0.f;};
    void setTickrate(float tick){tickrate=tick;};
private:
    float tickrate;
    float time;
};



