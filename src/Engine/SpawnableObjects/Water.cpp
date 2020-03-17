

#include "Water.h"

Water::Water(StateEssentials &es, glm::vec3 origin, float WaveSize,
             float WaterBodySize, glm::vec3 waterColor, float speed) :essentials(es){
    m_origin = origin;
    m_waveSize = WaveSize;
    m_speed = speed;
    noise.SetNoiseType(FastNoise::Simplex);
    noise.SetFrequency(0.2);
    m_waterbodySize = WaterBodySize;
    m_waterColor = waterColor;
    trianglesPerSide = static_cast<unsigned int>(m_waterbodySize/m_waveSize);

    PROGRAMM=essentials.loader.createProgram({{"water_vertex.glsl",ShaderLoader::VERTEX},
                                 {"water_fragment.glsl",ShaderLoader::FRAGMENT}});

    std::vector<glm::vec3> rawVertices;
    for(int x =0;x<trianglesPerSide;x++)
    {
        for(int z=0; z<trianglesPerSide;z++)
        {
            float y = noise.GetNoise(x,z);
            y+=1.f;
            y/=2.f;
            rawVertices.emplace_back((float)x,y,(float)z);
        }
    }

    //FORMAT = (x,y,z,x1,y1,z1,x2,y2,z3),(x,y,z,x1,y1,z1,x2,y2,z3)
    for(int x = 0;x<trianglesPerSide-1;x++)
        for(int z=0;z<trianglesPerSide-1;z++)
        {
            glm::vec3 main,sec,tri;
            //inject first triangle
            auto pos_in_vector = (x*trianglesPerSide)+z;
            main = rawVertices[pos_in_vector];
            sec = rawVertices[pos_in_vector+1];
            tri = rawVertices[pos_in_vector+trianglesPerSide];
            waterVertices.insert(waterVertices.end(),{main,sec,tri});
            //inject second triangle
            main = rawVertices[pos_in_vector+trianglesPerSide];
            sec = rawVertices[pos_in_vector+1];
            tri = rawVertices[pos_in_vector+1+trianglesPerSide];
            waterVertices.insert(waterVertices.end(),{main,sec,tri});
        }
    waterVertices.shrink_to_fit();

    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,waterVertices.size()*sizeof(glm::vec3),waterVertices.data(),GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*) sizeof(glm::vec3));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)(sizeof(glm::vec3) + sizeof(glm::vec3)));
    glEnableVertexAttribArray(2);
}

void Water::render() {
    float elapsed =  clock.restart().asSeconds();
    essentials.loader.setUniform(glm::fvec3(1.0,1.0,1.0),"WaterColor");
    essentials.loader.setUniform(float(1.0),"degrees");
}

void Water::update(float elapsed) {

}



