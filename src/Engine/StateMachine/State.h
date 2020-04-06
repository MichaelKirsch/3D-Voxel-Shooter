

#pragma once
#include "Essential.h"

class State {
public:
    State(){};
    virtual void updateFrame(float& elapsed){};
    virtual void updateEntities(float& elapsed){};
    virtual void processInputs(float& elapsed){};
    ~State()= default;
};



