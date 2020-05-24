

#pragma once

#include <iostream>
#include "StateMachine/State.h"
#include "Sun.h"
#include "Water.h"
#include "SFML/Graphics.hpp"
#include "Terrain.h"
#include "StateMachine/SimpleTimer.h"
#include "Ammo.h"
#include "Generators/TerrainGenerator.h"
#include "glm/glm/gtx/rotate_vector.hpp"
#include <cmath>
#include "Timer.h"
#include "Player.h"
#include "TextStuff/Font.h"
#include "TextStuff/SimpleText.h"
#include "Terrain/ImprovedTerrain.h"
#include "Terrain/ImprovedWater.h"
#include "StopWatch.h"
#include "ProjectileGenerator.h"

class GameOver : public State {
public:
    GameOver();
    void updateFrame(float& elapsed);
    void updateEntities(float& elapsed);
    void processInputs(float& elapsed);
    ~GameOver()
    {
    };

private:
    Sun sun;
    ProjectileGenerator pr_gen;
    ImprovedTerrain new_terrain;
    ImprovedWater new_water;
    Font font;
    SimpleText text,text2,text3,text4;
    unsigned int programm;
    Player player,bot;
    std::list<std::unique_ptr<Player>> m_Bots;
    sf::Mouse m_Mouse;
    float last_time;
    bool mouse_hold;
    sf::Sound shot,hit;
    sf::SoundBuffer shotsound,hitbuffer;
    bool wire;
    sf::Clock shotTimer;
    float shot_timer;
    SimpleTimer timer;
    int hitcounter =0;
protected:
};



