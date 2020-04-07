

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
#include <queue>
#include "ShaderLoader.h"

class ChunkManager : public Renderable {
public:
    ChunkManager(StateEssentials& es);
    void render() override;

    void update(float &elapsed) override;

    void create(TerrainGenerator* ter,unsigned int viewDistance=10, int chunksize=32);

    glm::ivec3 chunkPositionPlayer;
    int getAverage();
    int getCreated();
    ~ChunkManager() = default;
private:
    void refactorChunkStructure();
    void deleteOldChunks();
    void createNewChunks();
    std::unordered_map<glm::ivec3,Chunk> loaded_chunks;
    std::queue<glm::ivec3> to_create;
    std::stack<glm::ivec3> to_delete;
    std::vector<glm::ivec3> chunksThatHaveToBeThere;
    StateEssentials& stateEssentials;
    TerrainGenerator* terrainGenerator;
    std::vector<glm::ivec3> generateChunkGrid();
    unsigned int PROGRAMM;
    std::vector<glm::ivec3> originChunkPositions;
    int m_chunksize, m_viewDistance;
    SimpleTimer timer;

    bool comparevector(glm::ivec3& v1,glm::ivec3& v2);
    unsigned int created_chunks, chunksizes;
    unsigned int average_chunksize;
protected:
};



