

#pragma once

#include "ImprovedTerrain.h"
#include "Renderable.h"
#include "ShaderLoader.h"


struct WaterTile
{
    glm::uint16 x_pos_base;
    glm::uint16 z_pos_base;
    glm::float32 y_pos_leftup;
    glm::float32 y_pos_rightup;
    glm::float32 y_pos_leftbottom;
    glm::float32 y_pos_rightbottom;
};

struct WaterVertex
{
    glm::uint16 posx;
    glm::uint16 posz;
    glm::float32 posy_own;
    glm::uint8 vertex;
    glm::uint8 unused;
    glm::uint16 unused2;
};


class ImprovedWater : public Renderable{
public:
    ImprovedWater();

    void render() override;

    void update(float &elapsed) override;

    float waveheight;

    void create(ImprovedTerrain& r_terrain,float waterlevel = 0.05f);

    ~ImprovedWater();

private:
    enum direction
    {
        nw=0,ne,sw,se
    };
    FastNoise m_noise;
    std::vector<glm::vec3> vbo_data;
    unsigned int VBO,VAO,PROGRAMM;
    ImprovedTerrain* p_terrain;
    std::vector<WaterTile> raw_tiles;
    int m_waterlevel;
    WaterTile generateTile(int x, int z);
    const float size = 0.5f;
    void convertWatertileToFloatAndAddToVBOdata(WaterTile tile);
    glm::vec3 waterVertexToRaw(WaterVertex vert);
protected:
};



