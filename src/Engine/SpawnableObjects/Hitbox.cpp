

#include "Hitbox.h"

bool Hitbox::collisionDetectionHitboxes(Hitbox &hitBoxToCheck) {
    return (minx <= hitBoxToCheck.maxx && maxx >= hitBoxToCheck.minx) &&
           (miny <= hitBoxToCheck.maxy && maxy >= hitBoxToCheck.miny) &&
           (minz <= hitBoxToCheck.maxz && maxz >= hitBoxToCheck.minz);
}

void Hitbox::createHitbox(glm::vec3 i_origin, float i_size) {
    originOfHitbox = i_origin;
    size = i_size;
    minx = originOfHitbox.x-i_size;
    maxx = originOfHitbox.x+i_size;
    miny = originOfHitbox.y-i_size;
    maxy = originOfHitbox.y+i_size;
    minz = originOfHitbox.z-i_size;
    maxz = originOfHitbox.z+i_size;
}

Hitbox::Hitbox(glm::vec3 i_origin, float i_size) {
    createHitbox(i_origin,i_size);
}

bool Hitbox::collisionDetectionPoint(glm::vec3 point) {
    return (point.x >= minx && point.x <= maxx) &&
           (point.y >= miny && point.y <= maxy) &&
           (point.z >= minz && point.z <= maxz);
}
