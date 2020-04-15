

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
    int getWaterlevel();
    void create(glm::vec3 offset,unsigned int i_size=600,int height=40,int seed=400, float i_freq=0.0001, float waterle=0.25f,float border=0.04f);

    void render() override;
    bool isBorder(int x,int z){ return borderFactor(x,z)<1.f;};
    void update(float &elapsed) override;
    int getSize(){ return m_size;};
    int getMaxTerrainHeight(){ return max_terrain_height;};

    int getHeightOfTerrain(int x,int z);

    std::vector<glm::vec3> m_VertexData;
private:
    std::vector<Vertex> generateMeshOfSingleBlock(int x, int y,int z);
    std::vector<Vertex> generateMeshDownwardsThisPoint(int x, int z);
    glm::vec3 convertMeshToVec3(Vertex& vertex);
    std::vector<Vertex> generateSide(glm::vec3 center, sides side, std::vector<int>order);
    std::bitset<6> determineBlockVisibility(int x, int y, int z);
    glm::vec3 m_offset;
    unsigned int m_size;
    FastNoise m_noise,m_typenoise,m_grondTypeNoise;
    int m_seed;
    float waterlevel;
    unsigned int VBO,VAO,PROGRAMM;
    int max_terrain_height;
    float borderThiccccccccness;
    glm::vec3 getColor(glm::ivec3 position);


    float borderFactor(int x,int z);



    glm::vec3 getColorGradient(float noiseGradient, glm::vec3 color1, glm::vec3 color2);



};



