

#include "GameOver.h"

GameOver::GameOver(ShaderLoader &shloader, WindowManager& win) : State(shloader), water(shloader),m_windowmanger(win) {
    programm=shloader.createProgram({{"platform_fragment",ShaderLoader::FRAGMENT},{"platform_vertex",ShaderLoader::VERTEX}});
}

void GameOver::updateFrame() {
    m_windowmanger.clearScreen();
    water.render();
    m_windowmanger.swapBuffers();
}

void GameOver::updateEntities() {
    water.update(0.5f);
}

void GameOver::processInputs() {
    sf::Event ev;
    while(m_windowmanger.getWindow().pollEvent(ev))
    {
        if(ev.type == sf::Event::Closed)
        {

        }
    }
}
