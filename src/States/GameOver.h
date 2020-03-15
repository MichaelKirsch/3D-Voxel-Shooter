

#pragma once

#include <iostream>
#include "StateMachine/State.h"
#include "WorldWater.h"
#include "SFML/Graphics.hpp"
#include "Terrain.h"
class GameOver : public State {
public:
    GameOver(StateEssentials& es);
    void updateFrame(float& elapsed);
    void updateEntities(float& elapsed);
    void processInputs(float& elapsed);
    ~GameOver() = default;

private:
    unsigned int programm;
    WorldWater water;
    sf::Mouse m_Mouse;
    float last_time;
    bool mouse_hold;
    Terrain terrain;
protected:
};



