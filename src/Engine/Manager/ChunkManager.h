

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
    void fillWorldInBeginning();
    std::map<unsigned long,Chunk> loaded_chunks;
    std::stack<unsigned int*> unused_buffers;
    std::vector<unsigned int> buffers;
    std::stack<std::pair<glm::ivec3,unsigned int>> chunks_to_delete;
    StateEssentials& stateEssentials;
    TerrainGenerator* terrainGenerator;
    std::vector<glm::ivec3> generateVisibleChunks();
    unsigned int VAO,VBO, PROGRAMM;
    unsigned int needed_buffers;
    std::vector<glm::ivec3> startChunkPositions;
    int m_chunksize, m_viewDistance;
    SimpleTimer timer;
    unsigned long hash_ivec(glm::ivec3 vector);
protected:
};



