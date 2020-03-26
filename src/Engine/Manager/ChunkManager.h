

#pragma once

#include <map>
#include <unordered_map>
#include <unordered_set>
#include "Renderable.h"
#include "StateMachine/Essential.h"
#include "Chunk.h"
#include "Generators/TerrainGenerator.h"
#include <stack>
#include "SimpleTimer.h"
#include <StopWatch.h>
#include <functional>
#include <gtx/hash.hpp>

class ChunkManager : public Renderable {
public:
    ChunkManager(StateEssentials& es);
    void render() override;

    void update(float &elapsed) override;

    void create(TerrainGenerator* ter,unsigned int viewDistance=10, int chunksize=32);

    glm::ivec3 chunkPositionPlayer;

    ~ChunkManager() = default;
private:
    void refactorChunkStructure();
    void deleteOldChunks();
    void createNewChunks();
    std::unordered_map<glm::ivec3,Chunk> loaded_chunks;
    std::stack<glm::ivec3> to_create;
    std::stack<glm::ivec3> to_delete;
    std::stack<glm::ivec3 > not_new;
    std::stack<unsigned int> unused_buffers;
    std::vector<unsigned int> buffers;

    StateEssentials& stateEssentials;
    TerrainGenerator* terrainGenerator;
    std::vector<glm::ivec3> generateChunkGrid();
    unsigned int VAO,VBO, PROGRAMM;
    unsigned int needed_buffers;
    std::vector<glm::ivec3> originChunkPositions;
    int m_chunksize, m_viewDistance;
    SimpleTimer timer;
    bool comparevector(glm::ivec3 v1,glm::ivec3 v2);
protected:
};



