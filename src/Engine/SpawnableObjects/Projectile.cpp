//
// Created by micha on 23.05.2020.
//

#include "Projectile.h"

Projectile::Projectile(glm::vec3 start_pos, glm::vec3 direction, float lifetime, float speed, float size) {
    m_lifetime = lifetime;
    m_speed = speed;
    m_position = start_pos;
    m_direction = direction;
    glm::normalize(direction);
    m_speed = speed;
    m_size = size;
}

void Projectile::update(float elapsed)
{
    m_lifetime-=elapsed;
    if(m_lifetime<=0.f)
        alife = false;
    float  distance_taveled = m_speed/elapsed;
    auto ves = m_direction*distance_taveled;
    m_position +=ves;
    m_position.y -=0.1f;
}
