

#include "Statemachine.h"

Statemachine::Statemachine() {
    running = true;
    essential.windowManager.create({1000,1000}, false);
    updateTimer.setTickrate(40);
    frameTimer.setTickrate(60);
    inputTimer.setTickrate(60);
    m_playedState = std::make_unique<GameOver>(essential);
    essential.shouldClose = false;
}

void Statemachine::run() {
    while(!essential.shouldClose)
    {
        float elapsed = m_clock.restart().asSeconds();
        updateTimer.setElapsed(elapsed);
        frameTimer.setElapsed(elapsed);
        inputTimer.setElapsed(elapsed);
        if(frameTimer.getState())
        {
            m_playedState->updateFrame();
        }
        if(inputTimer.getState())
        {
            m_playedState->processInputs();
        }
        if(updateTimer.getState())
        {
            m_playedState->updateEntities();
        }
    }
}
