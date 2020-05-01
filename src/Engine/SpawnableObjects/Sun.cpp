

#include "Sun.h"

void Sun::render() {
}

void Sun::update(float &elapsed) {
    m_degrees+=m_speed;
    sunPosition = {m_center.x+(cos(m_degrees)*m_radius),m_center.y,m_center.z+(sin(m_degrees)*m_radius)};
}

void Sun::create(glm::vec3 center, float radius, float speed, glm::vec4 color) {
    m_center = center;
    m_radius = radius;
    m_speed = speed;
    sunColor = color;
}
