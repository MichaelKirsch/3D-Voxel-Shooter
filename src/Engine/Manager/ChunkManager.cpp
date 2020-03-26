

#include "ChunkManager.h"

ChunkManager::ChunkManager(StateEssentials &es) : stateEssentials(es) {
    timer.setTickrate(5);
}

void ChunkManager::render() {

}

void ChunkManager::update(float &elapsed) {
    auto starting_point_raw = stateEssentials.camera.Position;
    chunkPositionPlayer = glm::ivec3(starting_point_raw.x / m_chunksize, 0, starting_point_raw.z / m_chunksize);
    refactorChunkStructure();
    deleteOldChunks();
    createNewChunks();
}

void ChunkManager::create(TerrainGenerator *ter, unsigned int viewDistance, int chunksize) {
    StopWatch watch;
    m_chunksize = chunksize;
    m_viewDistance = viewDistance;
    terrainGenerator = ter;
    auto starting_point_raw = stateEssentials.camera.Position;
    auto starting_point_chunk = glm::ivec3(starting_point_raw.x / m_chunksize, 0, starting_point_raw.z / m_chunksize);
    originChunkPositions = generateChunkGrid();
    buffers.resize(originChunkPositions.size());
    std::fill(buffers.begin(), buffers.end(), 1);
    glGenBuffers(originChunkPositions.size(), buffers.data());

    for (auto unused:buffers) {
        unused_buffers.push(unused);
    }
    std::cout << "Generated " << unused_buffers.size() << " unused buffers and " << to_create.size()
              << " chunks that are not buffered yet" << std::endl;
}

std::vector<glm::ivec3> ChunkManager::generateChunkGrid() {
    std::vector<glm::ivec3> chunks_needed;
    for (int steps = m_viewDistance; steps >= -m_viewDistance; steps--) {
        int x = steps;
        int z = std::sqrt((std::pow(m_viewDistance, 2) - std::pow(x, 2)));
        for (int iter = -z; iter <= z; iter++) {
            chunks_needed.emplace_back(glm::ivec3(x, 0, iter));
        }
    }
    return chunks_needed;
}

void ChunkManager::refactorChunkStructure() {
    StopWatch w;
    std::vector<glm::ivec3> chunksThatHaveToBeThere;
    for (auto &el:originChunkPositions) {
        chunksThatHaveToBeThere.emplace_back(glm::ivec3(el + chunkPositionPlayer));
    }
    for (auto &new_element:chunksThatHaveToBeThere) {
        bool is_in_there =false;
        for (auto& element:loaded_chunks) {
            if (comparevector(element.first, new_element)) {
                is_in_there= true;
            }
            if(is_in_there)
                break;
        }
        if(is_in_there)
            not_new.push(new_element);
        else
            to_create.push(new_element);
    }
    auto nnw = not_new.size();
    while (!not_new.empty()) {
        bool is_in_this_set=false;
        for(auto& element_that_is_needed:chunksThatHaveToBeThere)
        {
            if(comparevector(element_that_is_needed,not_new.top()))
            {
                is_in_this_set=true;
            }
            if(is_in_this_set)
                break;
        }
        if(!is_in_this_set)
        {
            to_delete.push(not_new.top());
        }

        not_new.pop();
    }
    auto time4 = w.stop();
    std::cout << "To be: "<< chunksThatHaveToBeThere.size() <<" | To create: " << to_create.size() << " | To delete: " << to_delete.size() << " | Not new: "<< nnw << " | Loaded: "
              << loaded_chunks.size()<< " | " << time4 << " microseconds" << std::endl;
}

    void ChunkManager::deleteOldChunks() {
        while (!to_delete.empty()) {
            unsigned int buffer_thats_freeed =loaded_chunks.at(to_delete.top()).VBO_ADRESS;
            unused_buffers.push(buffer_thats_freeed);
            loaded_chunks.erase(to_delete.top());
            to_delete.pop();
        }
    }

    void ChunkManager::createNewChunks() {
        while (!to_create.empty()) {
            unsigned int buf = unused_buffers.top();
            auto position_of_to_create = to_create.top();
            loaded_chunks.insert(std::make_pair(position_of_to_create,Chunk(terrainGenerator, position_of_to_create, m_chunksize, buf)));
            unused_buffers.pop();
            to_create.pop();
        }
    }

    bool ChunkManager::comparevector(glm::ivec3 v1, glm::ivec3 v2) {
        return (v1.x == v2.x) & (v1.y == v2.y) & (v1.z == v2.z);
    }





