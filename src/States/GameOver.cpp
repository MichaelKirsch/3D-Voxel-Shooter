

#include "GameOver.h"


GameOver::GameOver(StateEssentials &es) : State(es),water(es),terrain(es) {
    essentials.camera.Position = {10.f,10.f,10.f};
    essentials.camera.MovementSpeed = 60.0;
    water.create({0.f,0.f,0.f},1.0f,300.f);
}

void GameOver::updateFrame(float& elapsed) {
    essentials.windowManager.clearScreen();
    water.render();
    terrain.render();
    essentials.windowManager.swapBuffers();
}

void GameOver::updateEntities(float& elapsed) {
    water.update(elapsed);
}

void GameOver::processInputs(float& elapsed) {
    sf::Event ev;
    float time = 0.02;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        essentials.camera.ProcessKeyboard(FORWARD,time);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        essentials.camera.ProcessKeyboard(LEFT,time);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        essentials.camera.ProcessKeyboard(BACKWARD,time);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        essentials.camera.ProcessKeyboard(RIGHT,time);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if(wire)
            wire =0;
        else
            wire =1;
        if(wire)
        {
            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        }
        else
        {
            glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
        }

    }

    if(m_Mouse.isButtonPressed(sf::Mouse::Left))
    {
        essentials.camera.Position = {50,50,50};
    }


    float yaw,pitch;
    float x_percent =  (1.f/essentials.windowManager.getWindow().getSize().x) * m_Mouse.getPosition(essentials.windowManager.getWindow()).x;
    float y_percent =  (1.f/essentials.windowManager.getWindow().getSize().y) * m_Mouse.getPosition(essentials.windowManager.getWindow()).y;

    x_percent-=0.5f;
    y_percent-=0.5f;
    x_percent*=2;
    y_percent*=2;
    yaw = 180.f*x_percent;
    pitch = 180.f*-y_percent;

    if(m_Mouse.isButtonPressed(sf::Mouse::Right))
    {
        essentials.windowManager.getWindow().setMouseCursorVisible(false);
        essentials.camera.ProcessMouseMovement(yaw,pitch);
        m_Mouse.setPosition({static_cast<int>(essentials.windowManager.getWindow().getSize().x/2),static_cast<int>(essentials.windowManager.getWindow().getSize().y/2)},essentials.windowManager.getWindow());
    } else
    {
        mouse_hold = false;
        essentials.windowManager.getWindow().setMouseCursorVisible(true);
    }

    while(essentials.windowManager.getWindow().pollEvent(ev))
    {
        if(ev.type == sf::Event::Closed)
        {
            essentials.shouldClose = true;
        }
    }
}


