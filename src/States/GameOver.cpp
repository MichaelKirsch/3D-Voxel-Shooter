

#include "GameOver.h"


GameOver::GameOver(StateEssentials &es) : State(es),water(es),terrain(es),ammo(es),terrainGenerator(es),player(terrain,es) {
    essentials.camera.MovementSpeed = 20.f;
    int size = 700;
    timer.setTickrate(0.5);
    terrain.create({0.f,0.f,0.f},400,size,25.f,0.3f,0.005f);
    water.create(terrain,{-100.f,0.f,-100.f},1.0f,size+200,{0, 0.337, 0.921},0.06f,0.15f,0.1);
    ammo.create(terrain,700,1.0);
    text.create(es,"JetBrainsMono-Medium.ttf");
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //player.respawn({10,10,10}, false);
    player.horizontal_velocity =0.f;
    bool found = 0;
    while(!found)
    {
        auto x = rand()%terrain.getSize();
        auto z = rand()%terrain.getSize();
        if(terrain.getY(x,z)>4&&terrain.getY(x,z)<100)
        {
            found=true;
            player.respawn({x,terrain.getY(x,z),z});
        }
    }



}

void GameOver::updateFrame(float& elapsed) {
    essentials.windowManager.clearScreen();
    water.render();
    terrain.render();
    ammo.render();
    text.render();
    essentials.windowManager.swapBuffers();
}

void GameOver::updateEntities(float& elapsed) {
    player.update(elapsed);
    water.update(elapsed);
    std::cout << player.playerPos.x << "|" << player.playerPos.y << "|" << player.playerPos.z << std::endl;
    for(auto& package:ammo.packages)
    {
        auto dist = glm::distance(package.position,essentials.camera.Position);

        if(dist<10.f)
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
            {
                if(package.respawnTimer<=0.01)
                {
                    package.take();
                    ammo.playPickup();
                }

                ammo.need_refactor = true;
            }
        }
    }
    float test= 0.05f;
    ammo.update(test);
}

void GameOver::processInputs(float& elapsed) {

    sf::Event ev;
    player.processInputs();
    essentials.camera.Position = glm::vec3(player.playerPos.x,player.playerPos.y+4,player.playerPos.z);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) {
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
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
            essentials.camera.ProcessMouseScroll(deltamouse,1.5f);
        }
    }
}


