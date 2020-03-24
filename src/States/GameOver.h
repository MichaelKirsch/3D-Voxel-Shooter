

#pragma once

#include <iostream>
#include "StateMachine/State.h"
#include "Water.h"
#include "SFML/Graphics.hpp"
#include "Terrain.h"
#include "StateMachine/SimpleTimer.h"
#include "Food.h"
#include "Chunk.h"
#include "Generators/TerrainGenerator.h"
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
    Food food;
    sf::Mouse m_Mouse;
    float last_time;
    bool mouse_hold;
    Terrain terrain;
    TerrainGenerator terrainGenerator;
    bool wire;
    SimpleTimer timer;
protected:
};



