

#include "Statemachine.h"

Statemachine::Statemachine() {
    running = true;
    updateTimer.setTickrate(50);
    frameTimer.setTickrate(60);
    inputTimer.setTickrate(80);
}

void Statemachine::run() {
    while(running)
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
