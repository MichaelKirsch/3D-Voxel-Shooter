

#pragma once
#include "Renderable.h"
#include "StateMachine/Essential.h"
#include "SFML/Graphics.hpp"
#include "FastNoise/FastNoise.h"
class Water : public Renderable{
public:
    Water(StateEssentials& es);
    void create(glm::vec3 origin=glm::vec3(0.0f,0.0f,0.0f), float WaveSize=1.f,
            float WaterBodySize = 100.f, glm::vec3 waterColor={0.266, 0.466, 0.933},float speed=0.05f,float waveheight = 0.2f);
    void render() override;

    void update(float& elapsed) override;

    ~Water();
    //TODO destroy buffers

private:
    FastNoise noise;
    glm::vec3 m_origin, m_waterColor;
    unsigned int VAO, VBO, PROGRAMM;
    float m_speed,m_waterbodySize, m_waveSize, m_degrees,m_waveheight;
    unsigned int trianglesPerSide;
    StateEssentials& essentials;
    std::vector<glm::vec3> waterVertices;
protected:
};



