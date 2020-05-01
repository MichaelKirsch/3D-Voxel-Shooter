

#pragma once
#include "glm.hpp"
#include "Renderable.h"
class Sun : public Renderable {
public:
    void render() override;

    void update(float &elapsed);

    void create(glm::vec3 center, float radius, float speed, glm::vec4 color);

    ~Sun() = default;

    glm::vec3 sunPosition;
    glm::vec4 sunColor={0.901f, 0.835f, 0.537f, 1.f};
private:


    glm::vec3 m_center={0.f,30.f, 0.f};
    float m_radius=10.f;
    float m_speed=0.1f;
    float m_degrees=0.f;
};



