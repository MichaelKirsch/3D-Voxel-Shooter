

#include "Statemachine.h"

Statemachine::Statemachine()  : m_windowmanager({1000,1000},false){
    running = true;
    updateTimer.setTickrate(40);
    frameTimer.setTickrate(60);
    inputTimer.setTickrate(80);
    m_playedState = std::make_unique<GameOver>(m_shaderloader,m_windowmanager);
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
