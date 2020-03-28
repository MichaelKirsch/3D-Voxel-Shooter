

#pragma once

#include "Water.h"
#include "Renderable.h"
#include "Generators/Cube.h"
#include "Generators/TerrainGenerator.h"
#include <chrono>

class Chunk : public Renderable {
public:
    Chunk(TerrainGenerator* gen, glm::ivec3 pos,int chunksize, unsigned int programm);
    glm::vec3 position;
    int active_blocks=0;
    unsigned int VBO, VAO;
    std::vector<Cube> Blocks;
    int microseconds_needed;
    ~Chunk();
};



