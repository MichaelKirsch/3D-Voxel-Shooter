

#include "GameOver.h"


GameOver::GameOver() : player(new_terrain),bot(new_terrain){
    srand(time(NULL));
    StateEssentials::get().camera.MovementSpeed = 20.f;
    int size = 700;
    StateEssentials::get().windowManager.setClearColor({0.019, 0.862, 1,1.0});
    timer.setTickrate(0.5);
    StopWatch watch;
    new_terrain.create({0,0,0},500,64,rand()%1000,0.003,0.3f,0.02f);
    new_water.create(new_terrain);
    std::cout << "Took: " << std::to_string(watch.stop(StopWatch::milli))<< " milliseconds to build "<< new_terrain.m_VertexData.size() << " Vertices"<< std::endl;

    font.loadNewFont("JetBrainsMono-Regular.ttf",200);
    text.create({-0.9,0.8},&font,120,"Player:");
    text2.create({-0.9,0.9},&font,120,"HELLO WORLD");
    text3.create({-0.9,0.7},&font,120,"HELLO WORLD");
    text4.create({-0.9,0.6},&font,120,"HELLO WORLD");
    std::cout <<"new ter:" << new_terrain.m_VertexData.size()<<std::endl;

    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    player.horizontal_velocity =0.f;
    auto x = rand()%new_terrain.getSize();
    auto z = rand()%new_terrain.getSize();
    bot.respawn({x,new_terrain.getMaxTerrainHeight()+2,z});

}

void GameOver::updateFrame(float& elapsed) {
    StateEssentials::get().windowManager.clearScreen();
    StateEssentials::get().camera.Position = glm::vec3(player.playerPos.x,player.playerPos.y+6,player.playerPos.z); //needs to be here because of artifacts
    new_terrain.render();
    new_water.render();
    //player.render();
    //bot.render();
    text.render();
    text2.render();
    StateEssentials::get().windowManager.swapBuffers();
}

void GameOver::updateEntities(float& elapsed) {
    new_water.update(elapsed);
    player.update(elapsed);
    bot.update(elapsed);

    if(bot.hitbox.collisionDetectionHitboxes(player.hitbox))
    {
        player.setColor({1.f,0.2f,0.f});
        bot.setColor({1.f,0.2f,0.f});
    } else{
        player.setColor({0.3,0.3,0.3});
        bot.setColor({0.3,0.3,0.3});
    }
    float test= 0.05f;
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


