

#pragma once

#include <iostream>
#include "StateMachine/State.h"
#include "WorldWater.h"
#include "SFML/Graphics.hpp"
class GameOver : public State {
public:
    GameOver(StateEssentials& es);
    void updateFrame();
    void updateEntities();
    void processInputs();
    ~GameOver() = default;

private:
    unsigned int programm;
    WorldWater water;
protected:
};



