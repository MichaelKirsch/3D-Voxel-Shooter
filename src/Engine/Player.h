

#pragma once

#include "Terrain.h"
#include "Essential.h"
#include "Renderable.h"

class Player : public Renderable{
public:
    Player(Terrain& terrain);

    void respawn(glm::vec3 respawnPosition, bool bindToTerrain=true);

    void processInputs();

    virtual void render();

    virtual void update(float &elapsed);

    virtual void create();
    
    glm::vec3 playerPos;
    glm::vec3 lookingAt;
    float vertical_velocity;
    float horizontal_velocity;
    float playerSpeed;
    ~Player() = default;

private:
    sf::Mouse m_Mouse;
    unsigned int VAO, VBO;
    glm::vec3 up = {0.f,1.f,0.f};
    Terrain& ter;
protected:
};



