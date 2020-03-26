

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
    }
}

void ChunkManager::create(TerrainGenerator *ter, unsigned int viewDistance, int chunksize) {
    StopWatch watch;
    m_chunksize=chunksize;
    m_viewDistance = viewDistance;
    terrainGenerator = ter;
    auto starting_point_raw = stateEssentials.camera.Position;
    auto starting_point_chunk = glm::ivec2(starting_point_raw.x / m_chunksize, starting_point_raw.z / m_chunksize);
    startChunkPositions = generateVisibleChunks();
    buffers.reserve(startChunkPositions.size());
    std::fill(buffers.begin(),buffers.end(),1);
    glGenBuffers(startChunkPositions.size(),buffers.data());
    fillWorldInBeginning();
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

void ChunkManager::fillWorldInBeginning() {
    StopWatch w;
    for(auto& element:startChunkPositions)
    {
        loaded_chunks.insert(std::make_pair(hash_ivec(element),Chunk(terrainGenerator,element,m_chunksize)));
    }
    auto am = startChunkPositions.size();
    auto tim = w.stop(StopWatch::milli);
    std::cout << "Generated "<<am << " chunks in " <<tim/1000.f <<" seconds and it took ~"<< tim/am <<"ms per chunk"<<std::endl;
}

unsigned long ChunkManager::hash_ivec(glm::ivec3 vector) {
    return std::hash<int>()(vector.x)+std::hash<int>()(vector.y)+std::hash<int>()(vector.z);
}




