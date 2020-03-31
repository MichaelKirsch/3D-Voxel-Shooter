

#pragma once
#include "Renderable.h"
#include "Generators/Cube.h"
#include "Generators/TerrainGenerator.h"
#include <chrono>


class MeshedChunk : public Renderable {
public:
    MeshedChunk(TerrainGenerator *gen, glm::ivec3 pos, int chunksize);

    ~MeshedChunk() = default;

private:
protected:
};



