

#pragma once

#include "Water.h"
#include "Renderable.h"
#include "Generators/Cube.h"
#include "Generators/TerrainGenerator.h"
#include <chrono>

class Chunk : public Renderable {
public:
    Chunk(TerrainGenerator* gen, glm::ivec3 pos,int chunksize);
    glm::vec3 position;
    unsigned int size;
    std::vector<Cube> Blocks;
    ~Chunk();
    void deleteBuffers();
    unsigned int m_VAO, m_VBO;
};



