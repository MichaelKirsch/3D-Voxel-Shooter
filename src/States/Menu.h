

#pragma once

#include "StateMachine/State.h"
class Menu : public State{
public:
    Menu();

    void updateFrame(float &elapsed) override;

    void updateEntities(float &elapsed) override;

    void processInputs(float &elapsed) override;

    ~Menu();

private:
protected:
};



