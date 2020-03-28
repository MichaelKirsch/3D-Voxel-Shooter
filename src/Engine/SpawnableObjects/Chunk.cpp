

#include "Chunk.h"


Chunk::Chunk(TerrainGenerator *gen, glm::ivec3 pos, int chunksize, unsigned int Programm) {
    position = glm::vec3(pos);
    auto amount_blocks = chunksize * chunksize * chunksize;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    //lets resize the vector to fit the chunk
    active_blocks = 0;
    Blocks.resize(amount_blocks);
    int iterator = 0;
    for (auto &bl:Blocks) {
        glm::ivec3 v;
        v.x = iterator % chunksize;
        v.y = (iterator / chunksize) % chunksize;
        v.z = iterator / (chunksize * chunksize);
        glm::vec3 colRaw = {rand() % 100, rand() % 100, rand() % 100};
        colRaw *= 0.01f;
        bl.blockID_and_sides = colRaw;
        iterator++;
    }
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, Blocks.size() * sizeof(Cube), Blocks.data(), GL_STATIC_DRAW);
    auto loc =  glGetAttribLocation(Programm,"aPos");

    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, sizeof(Cube), (void *) 0);
    glEnableVertexAttribArray(loc);
    glBindVertexArray(1);
}
Chunk::~Chunk() {
    glDeleteBuffers(1,&VBO);
    glDeleteVertexArrays(1,&VAO);
}


