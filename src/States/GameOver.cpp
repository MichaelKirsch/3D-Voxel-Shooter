

#include "GameOver.h"


GameOver::GameOver(StateEssentials &es) : State(es),water(es),terrain(es),food(es),terrainGenerator(es),chunkManager(es) {
    essentials.camera.MovementSpeed = 60.0;
    int size = 700;
    timer.setTickrate(0.5);
    terrain.create({0.f,0.f,0.f},400,size,25.f,0.3f,0.01f);
    water.create(terrain,{-100.f,0.f,-100.f},1.0f,size+200,{0, 0.337, 0.921},0.06f,0.15f,0.1);
    food.create(terrain,7000,1.0);
    terrainGenerator.setUpGenerator();
    chunkManager.create(&terrainGenerator);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
}

void GameOver::updateFrame(float& elapsed) {
    essentials.windowManager.clearScreen();
    water.render();
    terrain.render();
    food.render();
    essentials.windowManager.swapBuffers();
}

void GameOver::updateEntities(float& elapsed) {
    water.update(elapsed);
    food.update(elapsed);
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
        const float mouse_boundaries = 0.03f;
        auto bound_pixels_x = mouse_boundaries*essentials.windowManager.getWindow().getSize().x;
        auto bound_pixels_y = mouse_boundaries*essentials.windowManager.getWindow().getSize().y;
        if(m_Mouse.getPosition(essentials.windowManager.getWindow()).x<bound_pixels_x)
        {
            essentials.camera.ProcessKeyboard(LEFT,time);
        }
        if(m_Mouse.getPosition(essentials.windowManager.getWindow()).x>essentials.windowManager.getWindow().getSize().x-bound_pixels_x)
        {
            essentials.camera.ProcessKeyboard(RIGHT,time);
        }

        if(m_Mouse.getPosition(essentials.windowManager.getWindow()).y<bound_pixels_y)
        {
            essentials.camera.ProcessKeyboard(FORWARD,time);
        }
        if(m_Mouse.getPosition(essentials.windowManager.getWindow()).y>essentials.windowManager.getWindow().getSize().y-bound_pixels_y)
        {
            essentials.camera.ProcessKeyboard(BACKWARD,time);
        }

        mouse_hold = false;
        essentials.windowManager.getWindow().setMouseCursorVisible(true);
    }




    while(essentials.windowManager.getWindow().pollEvent(ev))
    {
        if(ev.type == sf::Event::Closed)
        {
            essentials.shouldClose = true;
        }
        if(ev.type == sf::Event::MouseWheelMoved)
        {
            int deltamouse = ev.mouseWheel.delta;
            essentials.camera.ProcessMouseScroll(deltamouse,10.5);
        }
    }
}


