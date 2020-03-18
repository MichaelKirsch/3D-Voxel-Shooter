

#include "Terrain.h"

Terrain::Terrain(StateEssentials &es) :essential(es) {

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

    float factor = 1.0;

    int size_border=size*border_thicccccnes;

    if(y<size_border)
    {
        float buf=(1.0/size_border)*y;
        if(buf<factor)
            factor=buf;
    }
    if(x<size_border)
    {
        float buf=(1.0/size_border)*x;
        if(buf<factor)
            factor=buf;
    }

    if(x>(size-size_border))
    {
        float bufx = x-(size-size_border);

        float buf=(1.0/size_border)*(size_border-bufx);
        if(buf<factor)
            factor=buf;
    }

    if(y>(size-size_border))
    {
        float bufy = y-(size-size_border);

        float buf=(1.0/size_border)*(size_border-bufy);
        if(buf<factor)
            factor=buf;
    }


    return factor;
}

void Terrain::create(glm::vec3 origin,int seed, int size, int height, float border_width) {
    m_size= size;
    m_height = height;
    auto possible_blocks = size*size*height;
    chunkData.resize(possible_blocks);
    std::fill(chunkData.begin(),chunkData.end(),BLOCK_TYPE::NONE);
    noise.SetNoiseType(FastNoise::Simplex);
    noise.SetFrequency(0.01);

    for(int x =0;x<size;x++)
    {
        for(int z =0;z<size;z++)
        {

            auto y = static_cast<int>(noise.GetNoise(x,z)*height);
            y*=calculateBorderFactor(x,z,size,border_width);
            y-=3;
            if(y>-1)
            {
                glm::ivec3 raw = glm::ivec3((int)x,(int)y,(int)z);
                raw+=origin;
                setBlocktype(raw,BLOCK_TYPE::GRASS);
                if(raw.y>1)
                {
                    setBlocktype(glm::ivec3(raw.x,raw.y-1,raw.z),BLOCK_TYPE::GRASS);
                }
            }
        }
    }


    if(chunkData[getPosInChunk(glm::ivec3(0,7,0))]==BLOCK_TYPE::GRASS)
        std::cout << chunkData.size();




    for(int x =0;x<chunkData.size();x++)
    {
        if(chunkData[x]==BLOCK_TYPE::GRASS)
        {
            positions.emplace_back(getPosFromInt(x));
            positions.emplace_back(glm::vec3(0, 0.6, 0.160));
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

int Terrain::getPosInChunk(glm::ivec3 position) {
    return position.x + position.y * m_size + position.z * m_size * m_height;
    //return (position.x*m_size)+(position.z*m_height)+position.y;
}

BLOCK_TYPE Terrain::getBlocktype(glm::ivec3 pos) {
    return chunkData[getPosInChunk(pos)];
}

void Terrain::setBlocktype(glm::ivec3 pos, BLOCK_TYPE type) {
    chunkData[getPosInChunk(pos)]=type;
}

void Terrain::clearBlock(glm::ivec3 pos) {
    chunkData[getPosInChunk(pos)]=BLOCK_TYPE::NONE;
}

glm::ivec3 Terrain::getPosFromInt(int pos) {
       glm::ivec3 v;
        v.x = pos % m_size;
        v.y = (pos / m_size) % m_height;
        v.z = pos / (m_size * m_height);
        return v;
}


