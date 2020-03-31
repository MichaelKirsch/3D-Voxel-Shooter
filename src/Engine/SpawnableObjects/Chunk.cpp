

#include "Chunk.h"


Chunk::Chunk(TerrainGenerator *gen, glm::ivec3 pos, int chunksize) {
    position = glm::vec3(pos);

    glm::ivec3 worldpos = {pos.x*chunksize,pos.y*chunksize,pos.z*chunksize};

    glGenVertexArrays(1,&m_VAO);
    glGenBuffers(1,&m_VBO);

    auto amount_blocks = chunksize * chunksize * chunksize;
    Blocks.reserve(amount_blocks);

    for(int x =0;x<chunksize;x++)
    {
            for(int z=0;z<chunksize;z++)
            {
                glm::ivec3 posInChunk = {x,0,z};
                auto position_in_World = glm::ivec3(posInChunk+worldpos);
                auto new_collum = gen->generateCubesBelow(position_in_World,posInChunk,chunksize);
                Blocks.insert(Blocks.end(),new_collum.begin(),new_collum.end());
            }
    }

    Blocks.shrink_to_fit();
    glBindVertexArray(m_VAO);
    if(m_VAO == 0)
        throw std::runtime_error("VAO cant have Adress 0");
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, Blocks.size() * sizeof(Cube), Blocks.data(), GL_STATIC_DRAW);
    size= Blocks.size();
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Cube), (void *) 0);
    glEnableVertexAttribArray(2);
}
Chunk::~Chunk() {
    //glDeleteBuffers(1,&m_VBO);
    //glDeleteVertexArrays(1,&m_VAO);
}

void Chunk::deleteBuffers() {
    glDeleteBuffers(1,&m_VBO);
    glDeleteVertexArrays(1,&m_VAO);
}


