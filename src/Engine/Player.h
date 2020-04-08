

#pragma once

#include "Terrain.h"
#include "Essential.h"
#include "Renderable.h"
#include "Hitbox.h"
#include "Ammo.h"


class Player : public Renderable{
public:
    Player(Terrain& terrain);

    void respawn(glm::vec3 respawnPosition, bool bindToTerrain= false);

    void stockUp(AmmoType type);

    int getAmmoAmount(AmmoType type){ return ammoStorage.at(type);};

    void processInputs();

    virtual void render();

    virtual void update(float &elapsed);

    virtual void create();
    
    glm::vec3 playerPos;
    glm::vec3 lookingAt;
    float vertical_velocity;
    float horizontal_velocity;
    float playerSpeed;
    float playerHorizontalSpeed;
    ~Player() = default;
    void setColor(glm::vec3 newCol){color_according_to_armor=newCol;};
    Hitbox hitbox;
private:
    std::map<AmmoType,int> ammoStorage;
    glm::mat4 model = glm::mat4(1.0);
    glm::vec3 color_according_to_armor = {0, 0.960, 0.145 };
    sf::Mouse m_Mouse;

    unsigned int VAO, VBO, EBO, PROGRAMM;
    glm::vec3 up = {0.f,1.f,0.f};
    Terrain& ter;

    const float size = 0.5f;
    std::vector<glm::vec3> playerVertices={
            {size,size,size},
            {size,size,-size},
            {size,-size,size},
            {size,-size,-size},
            {-size,size,size},
            {-size,size,-size},
            {-size,-size,size},
            {-size,-size,-size}
    };

    std::vector<unsigned int> playerIndices =
            {
                    7,1,3,
                    7,5,1,
                    3,1,0,
                    3,0,2,
                    0,4,6,
                    2,0,6,
                    4,5,7,
                    4,7,6,
                    5,4,1,
                    1,4,0,
                    3,2,1,
                    3,1,7
            };

protected:
};



