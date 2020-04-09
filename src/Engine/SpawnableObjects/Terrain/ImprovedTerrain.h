

#pragma once

#include "ShaderLoader.h"
#include "Renderable.h"
#include "FastNoise/FastNoise.h"
#include <bitset>

enum sides
{
    left=0,right,up,down,front,back,underwater,_spare_bit
};

struct Vertex
{
    //float 1
    glm::uint8 color_red;
    glm::uint8 color_green;
    glm::uint8 color_blue;
    glm::uint8 normal;

    //float 2
    glm::uint16 center_x;
    glm::uint16 center_y;

    //float3
    glm::uint16 center_z;
    glm::uint8 which_vertex;
    glm::uint8 _spare;
};

class ImprovedTerrain : public Renderable{
public:
    ImprovedTerrain();
    ~ImprovedTerrain();

    void create(unsigned int i_size=600, float i_freq=0.001, float border=0.25f);

    void render() override;

    void update(float &elapsed) override;

    std::vector<Vertex> generateMeshDownwardsThisPoint(int x, int z);

    glm::vec3 convertMeshToVec3(Vertex& vertex);

    std::vector<Vertex> generateMeshOfSingleBlock(int x, int y,int z);

    int getHeightOfTerrain(int x,int z);

    std::vector<Vertex> generateSide(glm::vec3 center, sides side, std::vector<int>order);

    std::bitset<6> determineBlockVisibility(int x, int y, int z);

    std::vector<glm::vec3> m_VertexData;
private:
    glm::vec2 centerOfTerrain;
    unsigned int m_size;
    FastNoise m_noise;
    int m_noiseSeed, m_terrainHeight;
    float m_noiseFrequency, m_borderTHICCCCNES;
    unsigned int VBO,VAO,EBO,PROGRAMM;
    const int max_terrain_height = 20;
};



