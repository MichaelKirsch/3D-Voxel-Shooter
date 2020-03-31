

#pragma once

#include <iostream>
#include "StateMachine/State.h"
#include "Water.h"
#include "SFML/Graphics.hpp"
#include "Terrain.h"
#include "StateMachine/SimpleTimer.h"
#include "Ammo.h"
#include "Generators/TerrainGenerator.h"
#include "glm/glm/gtx/rotate_vector.hpp"
#include <cmath>
#include "Timer.h"


class GameOver : public State {
public:
    GameOver(StateEssentials& es);
    void updateFrame(float& elapsed);
    void updateEntities(float& elapsed);
    void processInputs(float& elapsed);
    ~GameOver() = default;

private:
    unsigned int programm;
    Water water;
    Ammo ammo;
    sf::Mouse m_Mouse;
    float last_time;
    bool mouse_hold;
    Terrain terrain;
    TerrainGenerator terrainGenerator;
    bool wire;

    SimpleTimer timer;
protected:
};



