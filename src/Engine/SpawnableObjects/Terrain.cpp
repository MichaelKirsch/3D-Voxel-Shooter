

#include "Terrain.h"

Terrain::Terrain(StateEssentials &es, int seed, int size) :essential(es) {
    noise.SetNoiseType(FastNoise::Simplex);
    noise.SetFrequency(0.01);

    for(int x =0;x<size;x++)
    {
        for(int z =0;z<size;z++)
        {

            auto y = static_cast<int>(noise.GetNoise(x,z)*15.f);
            y*=calculateBorderFactor(x,z,size);
            positions.emplace_back(glm::vec3((float)x,(float)y,(float)z));
            positions.emplace_back(0.01* (rand()%100),0.01* (rand()%100),0.01* (rand()%100));
        }
    }

    ProgrammID = essential.loader.createProgram({
        {"terrain_fragment.glsl",ShaderLoader::FRAGMENT}
    ,{"terrain_vertex.glsl",ShaderLoader::VERTEX},
            {"terrain_geometry.glsl",ShaderLoader::GEOMETRY}});

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(glm::vec3)*positions.size(),positions.data(),GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);
}

void Terrain::render() {
    essential.loader.useProgramm(ProgrammID);
    glBindVertexArray(VAO);
    glm::mat4 model = glm::mat4(1.f);
    essential.loader.setUniform(essential.camera.GetViewMatrix(),"view");
    essential.loader.setUniform(essential.windowManager.perspectiveProjection,"projection");
    essential.loader.setUniform(model,"model");
    glDrawArrays(GL_LINES, 0, positions.size());
    glBindVertexArray(0);
}

void Terrain::checkForCracks() {

}

float Terrain::calculateBorderFactor(float x, float y, int size, float border_thicccccnes) {

    return 1.0;
}
