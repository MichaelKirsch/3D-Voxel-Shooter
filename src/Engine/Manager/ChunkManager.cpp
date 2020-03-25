

#include "ChunkManager.h"

ChunkManager::ChunkManager(StateEssentials &es): stateEssentials(es) {
    buffers.reserve(100);
    std::fill(buffers.begin(),buffers.end(),1);
    glGenBuffers(100,buffers.data());
}

void ChunkManager::render() {

}

void ChunkManager::update(float &elapsed) {
    auto starting_point_raw = stateEssentials.camera.Position;
    chunkPositionPlayer = glm::ivec2(starting_point_raw.x / m_chunksize, starting_point_raw.z / m_chunksize);

}

void ChunkManager::create(TerrainGenerator *ter, unsigned int viewDistance, int chunksize) {
    m_chunksize=chunksize;
    m_viewDistance = viewDistance;
    auto starting_point_raw = stateEssentials.camera.Position;
    auto starting_point_chunk = glm::ivec2(starting_point_raw.x / m_chunksize, starting_point_raw.z / m_chunksize);
}

std::vector<glm::ivec3> ChunkManager::generateVisibleChunks() {
    glm::ivec2 test = {0,0};
    std::vector<glm::ivec3> chunks_needed;
    int chunks_amount;
    auto start = std::chrono::steady_clock::now();
    for(int steps =m_chunksize; steps>=-m_chunksize;steps--)
    {
        int x =steps;
        int z = std::sqrt((std::pow(m_chunksize,2)-std::pow(x,2)));
        for(int iter=-z;iter<=z;iter++)
        {
            chunks_needed.emplace_back(glm::ivec3(x,0,z));
            chunks_needed.emplace_back(glm::ivec3(x,1,z));
            chunks_amount++;
        }

    }
    auto end = std::chrono::steady_clock::now();

    auto microseconds_needed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return chunks_needed;
}




