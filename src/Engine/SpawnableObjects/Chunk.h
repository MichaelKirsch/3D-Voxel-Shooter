

#pragma once

#include "Water.h"
#include "Renderable.h"
#include "Generators/Cube.h"
#include "Generators/TerrainGenerator.h"
#include <chrono>

class Chunk : public Renderable {
public:
    Chunk(TerrainGenerator& gen, glm::ivec3 position,int& chunksize);
    int active_blocks=0;
    ~Chunk() = default;
    std::vector<Cube> Blocks;
    int microseconds_needed;
private:
protected:
};



