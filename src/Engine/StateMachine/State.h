

#pragma once
#include "Essential.h"

class State {
public:
    State(StateEssentials& essentials) : essentials(essentials){};
    StateEssentials& essentials;
    virtual void updateFrame(){};
    virtual void updateEntities(){};
    virtual void processInputs(){};
    ~State()= default;
private:
protected:
};



