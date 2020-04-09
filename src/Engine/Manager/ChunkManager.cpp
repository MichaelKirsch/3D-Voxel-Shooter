

#include "ChunkManager.h"

ChunkManager::ChunkManager(StateEssentials &es) : stateEssentials(es) {
    timer.setTickrate(5);

    PROGRAMM =  ShaderLoader::createProgram({{"chunk.frag"},{"chunk.vert"},{"chunk.geom"}});
}

void ChunkManager::render() {
    ShaderLoader::useProgramm(PROGRAMM);
    for(auto& ind_chunk:loaded_chunks)
    {
        if(ind_chunk.second.m_VertexData.size()>0)
        {
            ind_chunk.second.render();
        }
    }
}

void ChunkManager::update(float &elapsed) {
    //determin if the player has moved and when yes delete old chunks. then every frame build a couple of the new chunks so nothing get clogged up
    auto starting_point_raw = stateEssentials.camera.Position;
    chunkPositionPlayer = glm::ivec3(starting_point_raw.x / m_chunksize, 0, starting_point_raw.z / m_chunksize);
    refactorChunkStructure();
    deleteOldChunks();
    createNewChunks();

}

void ChunkManager::create(unsigned int viewDistance, int chunksize) {
    StopWatch watch;
    m_chunksize = chunksize;
    m_viewDistance = viewDistance;
    auto starting_point_raw = stateEssentials.camera.Position;
    auto starting_point_chunk = glm::ivec3(starting_point_raw.x / m_chunksize, 0, starting_point_raw.z / m_chunksize);
    originChunkPositions = generateChunkGrid();
    std::cout << "chunks: "<<originChunkPositions.size()<<" Blocks: "<< m_chunksize*m_chunksize*m_chunksize*originChunkPositions.size()<<std::endl;
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
    chunksThatHaveToBeThere.clear();
    for (auto &el:originChunkPositions) {
        chunksThatHaveToBeThere.emplace_back(glm::ivec3(el + chunkPositionPlayer));
    }
    for (auto &new_element:chunksThatHaveToBeThere) {
        bool is_in_there =false;
        for (auto& element:loaded_chunks) {
            auto cpv =element.first;
            if (comparevector(cpv, new_element)) {
                is_in_there= true;
            }
            if(is_in_there)
                break;
        }
        if(!is_in_there)
            to_create.push(new_element);
    }

    for(auto& existing_elements:loaded_chunks) {
        bool is_elemtent_there = false;
        auto existing = existing_elements.first;
        for (auto &needed:chunksThatHaveToBeThere) {
            if (comparevector(existing, needed)) {
                is_elemtent_there = true;
            }
            if (is_elemtent_there)
                break;
        }
        if (!is_elemtent_there) {
            to_delete.push(existing);
        }
    }
}

    void ChunkManager::deleteOldChunks() {
        if (!to_delete.empty()) {
            if(loaded_chunks.find(to_delete.top())!=loaded_chunks.end())
            {
                loaded_chunks.erase(to_delete.top());
                to_delete.pop();
            }
        }
    }

    void ChunkManager::createNewChunks() {
        if (!to_create.empty()) {
            auto position_of_to_create = to_create.back();
            created_chunks++;
            //loaded_chunks.insert(std::make_pair(position_of_to_create,ImprovedTerrain ));
            to_create.pop();
        }
    }

    bool ChunkManager::comparevector(glm::ivec3& v1, glm::ivec3& v2) {
        return (v1.x == v2.x) & (v1.y == v2.y) & (v1.z == v2.z);
    }

int ChunkManager::getAverage() {
    return chunksizes/created_chunks;
}

int ChunkManager::getCreated() {
    return created_chunks;
}





