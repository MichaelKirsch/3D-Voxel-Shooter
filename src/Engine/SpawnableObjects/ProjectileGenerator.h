#pragma once
#include "Projectile.h"
#include <list>
#include "Renderable.h"
#include <string>
#include "ShaderLoader.h"
#include "Essential.h"
#include "Terrain/ImprovedTerrain.h"
#include "Hitbox.h"
class ProjectileGenerator : public Renderable {
public:
    void render() ;

    void update();

    void create(ImprovedTerrain* ter,std::string frag,std::string vert,std::string geom);
    bool checkHitbox(Hitbox* toCheck);
    ~ProjectileGenerator(){
    };
    std::list<std::unique_ptr<Projectile>> m_projectiles;
private:
    ImprovedTerrain* m_ter;
    unsigned int VBO,VAO,PROGRAMM;
    sf::Clock m_clock;
    std::vector<float> m_gpudata;
};


