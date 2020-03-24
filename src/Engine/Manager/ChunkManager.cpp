

#include "ChunkManager.h"

ChunkManager::ChunkManager(StateEssentials &es): stateEssentials(es) {

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




