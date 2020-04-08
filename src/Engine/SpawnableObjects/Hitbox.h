

#pragma once
#include "glm.hpp"

class Hitbox {
public:
    Hitbox(glm::vec3 i_orig={0,0,0},float i_size=1.f);
    void createHitbox(glm::vec3 i_origin, float i_size);
    float size;
    void setPos(glm::vec3 position);
    glm::vec3 originOfHitbox;
    bool collisionDetectionHitboxes(Hitbox& hitBoxToCheck);
    bool collisionDetectionPoint(glm::vec3 point);
    ~Hitbox() = default;

protected:
    float minx,maxx,miny,maxy,minz,maxz;
};



