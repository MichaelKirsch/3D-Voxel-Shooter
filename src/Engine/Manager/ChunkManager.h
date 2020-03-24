

#pragma once

#include <map>
#include "Renderable.h"
#include "StateMachine/Essential.h"
#include "Chunk.h"
class ChunkManager {
public:
    ChunkManager(StateEssentials& es);

    ~ChunkManager() = default;

private:
    StateEssentials& stateEssentials;
    unsigned int VAO,VBO, PROGRAMM;
    std::map<glm::ivec3,Chunk> renderedChunks;
protected:
};



