

#include "Chunk.h"


Chunk::Chunk(TerrainGenerator *gen, glm::ivec3 pos, int &chunksize, unsigned int i_VBO_ADRESS) {
    position=pos;
    auto amount_blocks = chunksize*chunksize*chunksize;
    //lets resize the vector to fit the chunk
    active_blocks = 0;
    Blocks.resize(amount_blocks);
    std::fill(Blocks.begin(),Blocks.end(),Cube{});
    int iterator=0;
    for(int x=0;x<chunksize;x++)
    {
        for(int z=0;z<chunksize;z++)
        {
            for(int y =0;y<chunksize;y++)
            {
                glm::ivec3 worldpos = {(position.x*chunksize)+x,(position.y*chunksize)+y, (position.z*chunksize)+z};
                gen->getCubeAtPosition(worldpos, Blocks[iterator]);
                Blocks[iterator].data.position = {x,y,z};
            }
        }
    }
    auto end = std::chrono::steady_clock::now();
    VBO_ADRESS = i_VBO_ADRESS;
    glBindBuffer(GL_ARRAY_BUFFER,VBO_ADRESS);
    glBufferData(GL_ARRAY_BUFFER,Blocks.size()*sizeof(Cube),Blocks.data(),GL_STATIC_DRAW);
}


