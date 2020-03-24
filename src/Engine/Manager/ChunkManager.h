

#pragma once

#include <map>
#include "Renderable.h"
#include "StateMachine/Essential.h"
#include "Chunk.h"
#include "Generators/TerrainGenerator.h"

class ChunkManager : public Renderable {
public:
    ChunkManager(StateEssentials& es);

    void render() override;

    void update(float &elapsed) override;

    void create(TerrainGenerator* ter,unsigned int viewDistance=6, int chunksize=32);

    glm::ivec2 chunkPositionPlayer;

    ~ChunkManager() = default;

private:
    StateEssentials& stateEssentials;
    TerrainGenerator* terrainGenerator;
    unsigned int VAO,VBO, PROGRAMM, m_viewDistance;
    std::map<glm::ivec3,Chunk> renderedChunks;
    int m_chunksize;
protected:
};



