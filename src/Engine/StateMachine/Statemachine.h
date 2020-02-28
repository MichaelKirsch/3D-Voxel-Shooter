

#pragma once

#include <vector>
#include <memory>
#include "State.h"
#include "SFML/Graphics.hpp"
#include "Timer.h"
#include "States/GameOver.h"
#include "WindowManager.h"
#include "ShaderLoader.h"

class Statemachine {
public:
    Statemachine();
    void run();
    ~Statemachine() = default;

private:
    std::unique_ptr<State> m_playedState;
    sf::Clock m_clock;
    WindowManager m_windowmanager;
    ShaderLoader m_shaderloader;
    float time;
    Timer frameTimer,updateTimer,inputTimer;
    bool running;
};



