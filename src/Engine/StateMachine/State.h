

#pragma once
#include "Essential.h"

class State {
public:
    State(StateEssentials& essentials) : essentials(essentials){};
    StateEssentials& essentials;
    virtual void updateFrame(float& elapsed){};
    virtual void updateEntities(float& elapsed){};
    virtual void processInputs(float& elapsed){};
    ~State()= default;
private:
protected:
};



