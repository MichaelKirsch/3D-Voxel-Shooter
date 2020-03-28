

#pragma once

#include "Renderable.h"
#include "StateMachine/Essential.h"
#include "FastNoise/FastNoise.h"
enum class BLOCK_TYPE
{
    NONE,GRASS,DIRT,STONE,SAND
};


class Terrain : public Renderable {
public:
    Terrain(StateEssentials& es);
    void create(glm::vec3 origin ={0.f,0.f,0.f},int seed=100, int size=300,int height = 30.f,float border_width=0.2f,float frequency = 0.01);
    void render() override;
    int getHeight(){ return m_height;};
    BLOCK_TYPE getBlocktype(glm::ivec3 pos);
    void setBlocktype(glm::ivec3 pos,BLOCK_TYPE type);
    void clearBlock(glm::ivec3 pos);
    FastNoise& getNoise(){ return noise;};
    int getSize(){ return m_size;};
    glm::ivec3 getPosFromInt(int pos);
    std::vector<BLOCK_TYPE>& getTerrainData(){ return chunkData;};
    int getY(int x, int z);
    bool isTerrain(int x, int z);
    ~Terrain() = default;

private:
    int getPosInChunk(glm::ivec3 position);
    float calculateBorderFactor(float x , float y, int size,float border_thiccccness=.2);
    float m_border_factor;
    int m_size,m_height,m_freq;
    StateEssentials& essential;
    unsigned int VAO,VBO,ProgrammID;
    std::vector<glm::vec3> positions;
    std::vector<BLOCK_TYPE>chunkData;
    FastNoise noise;
protected:
};



