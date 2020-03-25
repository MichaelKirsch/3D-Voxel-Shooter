

#include "ChunkManager.h"

ChunkManager::ChunkManager(StateEssentials &es): stateEssentials(es) {
    timer.setTickrate(5);
}

void ChunkManager::render() {

}

void ChunkManager::update(float &elapsed) {
    if(timer.check(elapsed))
    {
        auto starting_point_raw = stateEssentials.camera.Position;
        chunkPositionPlayer = glm::ivec2(starting_point_raw.x / m_chunksize, starting_point_raw.z / m_chunksize);
        //std::cout << chunkPositionPlayer.x<< "|" << chunkPositionPlayer.y<<std::endl;
    }
}

void ChunkManager::create(TerrainGenerator *ter, unsigned int viewDistance, int chunksize) {
    m_chunksize=chunksize;
    m_viewDistance = viewDistance;
    auto starting_point_raw = stateEssentials.camera.Position;
    auto starting_point_chunk = glm::ivec2(starting_point_raw.x / m_chunksize, starting_point_raw.z / m_chunksize);
    startChunkPositions = generateVisibleChunks();
    buffers.reserve(startChunkPositions.size());
    std::fill(buffers.begin(),buffers.end(),1);
    glGenBuffers(startChunkPositions.size(),buffers.data());
    std::cout << "Chunks that will be buffered:"<<startChunkPositions.size();
}

std::vector<glm::ivec3> ChunkManager::generateVisibleChunks() {
    std::vector<glm::ivec3> chunks_needed;
    int chunks_amount;
    auto start = std::chrono::steady_clock::now();
    for(int steps =m_viewDistance; steps>=-m_viewDistance;steps--)
    {
        int x =steps;
        int z = std::sqrt((std::pow(m_viewDistance,2)-std::pow(x,2)));
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




