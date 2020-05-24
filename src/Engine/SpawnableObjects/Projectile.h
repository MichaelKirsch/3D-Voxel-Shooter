#pragma once
#include "Hitbox.h"
#include "glm.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>


struct Projectile
{
    Projectile(glm::vec3 start_pos,glm::vec3 direction, float lifetime,float speed, float size);
    virtual ~Projectile() = default;
    void update(float elapsed);
    bool alife=true;
    glm::fvec3 m_direction;
    glm::fvec3 m_position;
    float m_size=0.f;
    float m_lifetime=0.f;
    float m_speed = 0.f;
};


