

#include "WorldWater.h"

WorldWater::WorldWater(ShaderLoader& loader,unsigned int size, int seed) : m_loader(loader) {
    m_size = size;
    m_noise.SetNoiseType(FastNoise::SimplexFractal);
    m_noise.SetSeed(seed);
    PROG = loader.createProgram({{"water_fragment",ShaderLoader::FRAGMENT},
                                 {"water_vertex",ShaderLoader::VERTEX}});
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);


    /*
     * In the beginning we will fill the water with random values. after that the sinus function
     * will take over and control the waves
     */
    for(int x =0;x<size;x++)
    {
        for(int z =0;z<size;z++)
        {
            int y = m_noise.GetNoise(x,z);
            y+=1.0f;
            y/=2.f;
            positions.emplace_back(glm::vec3(x,y,z));
        }
    }
    generateElements();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size(), &elements[0], GL_STATIC_DRAW);

    update(0.f);

}

void WorldWater::render() {
    m_loader.useProgramm(PROG);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLE_STRIP,elements.size(),GL_UNSIGNED_INT,0);
    glBindVertexArray(0);
}

void WorldWater::update(float change) {
    for(auto points:positions)
    {
        points.y+=change;
        if(points.y>1.0f)
            points.y =0.f;
    }
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, positions.size()* sizeof(glm::vec3),&positions[0], GL_STATIC_DRAW);
}

void WorldWater::generateElements() {
    for(int x=0;x<m_size-1;x++)
    {
        for(int z =0;z<m_size-1;z++)
        {
            auto pos_in_vector = (x*m_size)+z;
            //lets generate the pelemts for the traingle strips
            elements.emplace_back(pos_in_vector);
            elements.emplace_back(pos_in_vector+1);
            elements.emplace_back(pos_in_vector+m_size);
            elements.emplace_back(pos_in_vector+1);
            elements.emplace_back(pos_in_vector+m_size+1);
            elements.emplace_back(pos_in_vector+m_size);
        }
    }
}
