

#pragma once

#include <map>
#include "Renderable.h"
#include "StateMachine/Essential.h"
#include "Chunk.h"
#include "Generators/TerrainGenerator.h"
#include <stack>

class ChunkManager : public Renderable {
public:
    ChunkManager(StateEssentials& es);

    void render() override;

    void update(float &elapsed) override;

    void create(TerrainGenerator* ter,unsigned int viewDistance=6, int chunksize=32);

    glm::ivec2 chunkPositionPlayer;

    std::map<glm::ivec3,Chunk> bufferedChunks;

    std::vector<glm::ivec3> frustumChunks;

    std::vector<glm::ivec3> loadedChunks;

    ~ChunkManager() = default;
private:
    std::stack<unsigned int*> unused_buffers;
    std::vector<unsigned int> buffers;
    StateEssentials& stateEssentials;
    TerrainGenerator* terrainGenerator;
    std::vector<glm::ivec3> generateVisibleChunks();
    unsigned int VAO,VBO, PROGRAMM, m_viewDistance;
    int m_chunksize;
protected:
};



