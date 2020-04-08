

#pragma once

#include "ShaderLoader.h"
#include "Renderable.h"
#include "FastNoise/FastNoise.h"

enum active_sides
{
    left,right,up,down,front,back,underwater,_spare_bit
};

struct Vertex
{
    //float 1
    glm::uint8 color_red;
    glm::uint8 color_green;
    glm::uint8 color_blue;
    glm::uint8 active_sides;

    //float 2
    glm::int16 position_x;
    glm::int16 position_y;

    //float 3
    glm::int16 position_z;
    glm::int16 _spare;
};

class ImprovedTerrain : public Renderable{
public:
    ImprovedTerrain();

    void create();

    void render() override;

    void update(float &elapsed) override;

    glm::vec3 convertVertexToDatastream(Vertex& vertex);

    ~ImprovedTerrain();

private:
    FastNoise m_noise;
    int m_noiseSeed;
    float m_noiseFrequency;
    unsigned int VBO,VAO,EBO,PROGRAMM;

protected:
};



