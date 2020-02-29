

#include "GameOver.h"


GameOver::GameOver(StateEssentials &es) : State(es),water(es) {
    programm=essentials.loader.createProgram({{"platform_fragment",ShaderLoader::FRAGMENT},{"platform_vertex",ShaderLoader::VERTEX}});
}

void GameOver::updateFrame() {
    essentials.windowManager.clearScreen();
    water.render();
    essentials.windowManager.swapBuffers();
}

void GameOver::updateEntities() {
    water.update(0.5f);
}

void GameOver::processInputs() {
    sf::Event ev;
    while(essentials.windowManager.getWindow().pollEvent(ev))
    {
        if(ev.type == sf::Event::Closed)
        {

        }
    }
}


