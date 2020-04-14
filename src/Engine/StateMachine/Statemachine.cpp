

#include "Statemachine.h"

StateEssentials StateEssentials::s_Instance;

Statemachine::Statemachine() {
    running = true;
    StateEssentials::get().windowManager.create({1920,1080}, false,45.f,4000.f);
    updateTimer.setTickrate(60);
    frameTimer.setTickrate(60);
    inputTimer.setTickrate(60);
    m_playedState = std::make_unique<GameOver>();
    StateEssentials::get().shouldClose = false;
}

void Statemachine::run() {
    while(!StateEssentials::get().shouldClose)
    {
        elapsed = m_clock.restart().asSeconds();
        updateTimer.setElapsed(elapsed);
        frameTimer.setElapsed(elapsed);
        inputTimer.setElapsed(elapsed);
        if(StateEssentials::get().windowManager.getWindow().hasFocus())
        {
            if(frameTimer.getState())
            {
                m_playedState->updateFrame(elapsed);
            }
            if(inputTimer.getState())
            {
                m_playedState->processInputs(elapsed);
            }
            if(updateTimer.getState())
            {
                m_playedState->updateEntities(elapsed);
            }
        } else
        {
            sf::Event e;
            while (StateEssentials::get().windowManager.getWindow().pollEvent(e))
            {}
        }
    }
}
