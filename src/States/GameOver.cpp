

#include "GameOver.h"


GameOver::GameOver() : player(new_terrain),bot(new_terrain){
    shotsound.loadFromFile("../data/sounds/shot.wav");
    hitbuffer.loadFromFile("../data/sounds/kenney_uiaudio/Audio/switch1.ogg");
    shot.setBuffer(shotsound);
    hit.setBuffer(hitbuffer);
    srand(time(NULL));
    StateEssentials::get().camera.MovementSpeed = 20.f;
    int size = 700;
    StateEssentials::get().windowManager.setClearColor({0.019, 0.862, 1,1.0});
    timer.setTickrate(0.5);
    StopWatch watch;
    new_terrain.create(&sun,{0,0,0},500,64,rand()%1000,0.003,0.3f,0.04f);
    new_water.create(new_terrain,&sun);
    std::cout << "Took: " << std::to_string(watch.stop(StopWatch::milli))<< " milliseconds to build "<< new_terrain.m_VertexData.size() << " Vertices"<< std::endl;
    for(int x =0;x<100;x++)
    {
        m_Bots.push_back(std::make_unique<Player>(new_terrain));
        m_Bots.back()->respawn({rand()%new_terrain.getSize(),new_terrain.getMaxTerrainHeight()*5,rand()%new_terrain.getSize()});
        m_Bots.back()->setColor({1, 0.058, 0.878});
    }

    font.loadNewFont("JetBrainsMono-Regular.ttf",200);
    text.create({-0.9,0.8},&font,120,"Player:");
    text2.create({-0.9,0.9},&font,120,"HELLO WORLD");
    text3.create({-0.9,0.7},&font,120,"HELLO WORLD");
    text4.create({-0.9,0.6},&font,120,"HELLO WORLD");
    sun.create({new_terrain.getSize()*9,new_terrain.getMaxTerrainHeight()+10000,new_terrain.getSize()/2},
            new_terrain.getSize(),.01f,{0.901, 0.835, 0.537,1.f});
    std::cout <<"new ter:" << new_terrain.m_VertexData.size()<<std::endl;

    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    player.horizontal_velocity =0.f;
    auto x = rand()%new_terrain.getSize();
    auto z = rand()%new_terrain.getSize();
    bot.respawn({x,new_terrain.getMaxTerrainHeight()+2,z});
    pr_gen.create(&new_terrain,"projectile.frag","projectile.vert","projectile.geom");
}

void GameOver::updateFrame(float& elapsed) {
    StateEssentials::get().windowManager.clearScreen();
    StateEssentials::get().camera.Position = glm::vec3(player.playerPos.x,player.playerPos.y+6,player.playerPos.z); //needs to be here because of artifacts

    for(auto& b:m_Bots)
        b->render();
    bot.render();
    pr_gen.render();
    player.render();
    new_terrain.render();
    new_water.render();
    text.render();
    text2.render();
    StateEssentials::get().windowManager.swapBuffers();
}

void GameOver::updateEntities(float& elapsed) {
    new_water.update(elapsed);
    player.update(elapsed);
    pr_gen.update();
    sun.update(elapsed);
    if(bot.hitbox.collisionDetectionHitboxes(player.hitbox))
    {
        player.setColor({1.f,0.2f,0.f});
        bot.setColor({1.f,0.2f,0.f});
    } else{
        player.setColor({0.3,0.3,0.3});
        bot.setColor({0.3,0.3,0.3});
    }
    float test= 0.05f;


    for(auto it = std::begin(m_Bots); it != std::end(m_Bots); ) {
        auto& pr = *it;
        pr->update(elapsed);
        if(pr_gen.checkHitbox(&pr->hitbox)) {
            if(hit.getStatus()!=sf::SoundSource::Playing)
                hit.play();
            hitcounter++;
            it = m_Bots.erase(it);
            m_Bots.push_back(std::make_unique<Player>(new_terrain));
            m_Bots.back()->respawn({rand()%new_terrain.getSize(),new_terrain.getMaxTerrainHeight()*5,rand()%new_terrain.getSize()});
            m_Bots.back()->setColor({1, 0.058, 0.878});
        } else {
            ++it;
        }
    }

    text2.setText("Projectiles: " + std::to_string(pr_gen.m_projectiles.size())+" Kills:"+std::to_string(hitcounter));
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
    shot_timer += shotTimer.restart().asSeconds();
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&shot_timer>=0.1f)
    {
        shot_timer = 0.f;
        auto g = StateEssentials::get().camera.Position;
        auto dir =StateEssentials::get().camera.Front;
        dir.y+=0.0001f*(-50+rand()%100);
        dir.x+=0.0001f*(-50+rand()%100);
        dir.z+=0.0001f*(-50+rand()%100);
        pr_gen.m_projectiles.push_back(std::make_unique<Projectile>(g,dir,3.f,0.05f,0.1f));
        shot.play();
        shot.setVolume(10);
    }
}


