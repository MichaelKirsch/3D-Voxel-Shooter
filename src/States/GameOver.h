

#pragma once

#include <iostream>
#include "StateMachine/State.h"
#include "WorldWater.h"
#include "WindowManager.h"
#include "SFML/Graphics.hpp"
class GameOver : public State {
public:
    GameOver(ShaderLoader& shloader, WindowManager& man);
    void updateFrame();
    void updateEntities();
    void processInputs();
    ~GameOver() = default;

private:
    unsigned int programm;
    WorldWater water;
    WindowManager& m_windowmanger;
protected:
};



