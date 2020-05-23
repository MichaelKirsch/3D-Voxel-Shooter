

#pragma once

#include "Renderable.h"
#include "StateMachine/Essential.h"
#include "Terrain.h"
#include "FastNoise/FastNoise.h"
#include "Hitbox.h"
#include "SFML/Audio.hpp"

enum class AmmoType {
    light, heavy, sniper
};


struct AmmoPackage {
    AmmoType m_type;
    Hitbox hitbox;
    glm::vec3 position;
    glm::vec3 color;
    bool isRespawning;
    float respawnTimer;
    void take() {
        isRespawning = true;
        switch (m_type) {
            case AmmoType::sniper:
                respawnTimer = 15.f;
                break;
            case AmmoType::light:
                respawnTimer = 15.f;
                break;
            case AmmoType::heavy:
                respawnTimer = 15.f;
                break;
        }
    }
    void update(float& elapsed,bool& refactor)
    {
        if(isRespawning)
        {
            respawnTimer-=elapsed;
            if(respawnTimer<0.f)
            {
                refactor = true;
                isRespawning = false;
            }

        }
    }
};

class Ammo : public Renderable {
public:

    Ammo();

    void playPickup();

    void render() override;

    void update(float &elapsed) override;

    void create(Terrain &ter, int amount, float respawntime);

    std::vector<AmmoPackage> packages;
    std::vector<glm::vec3> Graphicsbuffer;
    ~Ammo() = default;
    bool need_refactor;
private:
    sf::Sound sound;
    sf::SoundBuffer pickupsound;
    glm::mat4 model;
    unsigned int VAO, VBO, PROGRAMM,texture;
protected:
};



