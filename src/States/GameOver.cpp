

#include "GameOver.h"


GameOver::GameOver() : player(terrain),bot(terrain){

    StateEssentials::get().camera.MovementSpeed = 20.f;
    int size = 700;
    timer.setTickrate(0.5);
    terrain.create({0.f,0.f,0.f},rand()%1000,size,25.f,0.3f,0.004f);
    water.create(terrain,{-100.f,0.f,-100.f},1.0f,size+200,{0, 0.337, 0.921},0.06f,0.15f,0.1);
    ammo.create(terrain,800,1.0);

    font.loadNewFont("JetBrainsMono-Regular.ttf",50);
    text.create({-0.9,0.8},&font,120,"Player:");
    text2.create({-0.9,0.9},&font,120,"HELLO WORLD");

    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    player.horizontal_velocity =0.f;
    bool found = 0;
    while(!found)
    {
        auto x = rand()%terrain.getSize();
        auto z = rand()%terrain.getSize();
        if(terrain.getY(x,z)>4&&terrain.getY(x,z)<100)
        {
            found=true;
            bot.respawn({x,100,z});
        }
    }
}

void GameOver::updateFrame(float& elapsed) {
    StateEssentials::get().windowManager.clearScreen();
    StateEssentials::get().camera.Position = glm::vec3(player.playerPos.x,player.playerPos.y+4,player.playerPos.z); //needs to be here because of artifacts
    water.render();
    terrain.render();
    ammo.render();
    player.render();
    bot.render();
    text.render();
    text2.render();
    StateEssentials::get().windowManager.swapBuffers();
}

void GameOver::updateEntities(float& elapsed) {
    player.update(elapsed);
    water.update(elapsed);
    bot.update(elapsed);
    //std::cout << player.playerPos.x << "|" << player.playerPos.y << "|" << player.playerPos.z << std::endl;
    for(auto& package:ammo.packages)
    {
        auto dist = glm::distance(package.position,StateEssentials::get().camera.Position);

        if(dist<10.f)
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
            {
                if(package.respawnTimer<=0.01)
                {
                    player.stockUp(package.m_type);
                    package.take();
                    ammo.playPickup();
                }

                ammo.need_refactor = true;
            }
        }
    }

    if(bot.hitbox.collisionDetectionHitboxes(player.hitbox))
    {
        player.setColor({1.f,0.2f,0.f});
        bot.setColor({1.f,0.2f,0.f});
    } else{
        player.setColor({0.3,0.3,0.3});
        bot.setColor({0.3,0.3,0.3});
    }
    float test= 0.05f;
    ammo.update(test);
    text2.setText("Ammo| Light:"+std::to_string(player.getAmmoAmount(AmmoType::light))+
    " Heavy:"+std::to_string(player.getAmmoAmount(AmmoType::heavy))+
    " Sniper:"+std::to_string(player.getAmmoAmount(AmmoType::sniper)));
    text.setText("Player:"+std::to_string(player.playerPos.x)+"X "+std::to_string(player.playerPos.y)+"Y "+std::to_string(player.playerPos.z)+"Z");
}

void GameOver::processInputs(float& elapsed) {

    sf::Event ev;
    player.processInputs();


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) {
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
    }

    while(StateEssentials::get().windowManager.getWindow().pollEvent(ev))
    {
        if(ev.type == sf::Event::Closed)
        {
            StateEssentials::get().shouldClose = true;
        }
        if(ev.type == sf::Event::MouseWheelMoved)
        {
            int deltamouse = ev.mouseWheel.delta;
            StateEssentials::get().camera.ProcessMouseScroll(deltamouse,1.5f);
        }
    }
}


