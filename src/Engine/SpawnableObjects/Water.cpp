

#include "Water.h"

Water::Water(StateEssentials &es) :essentials(es){
}

void Water::render() {
    essentials.loader.useProgramm(PROGRAMM);
    essentials.loader.setUniform(m_waterColor,"WaterColor");
    essentials.loader.setUniform(essentials.windowManager.perspectiveProjection,"projection");
    essentials.loader.setUniform(essentials.camera.GetViewMatrix(),"view");
    essentials.loader.setUniform(m_degrees,"degrees");
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES,0,waterVertices.size()/3);
    glBindVertexArray(1);
}

void Water::update(float& elapsed) {
    m_degrees+=0.05f;
}

void Water::create(glm::vec3 origin, float WaveSize, float WaterBodySize, glm::vec3 waterColor, float speed) {
    m_origin = origin;
    m_waveSize = WaveSize;
    m_speed = speed;
    noise.SetNoiseType(FastNoise::Simplex);
    noise.SetFrequency(0.2);
    m_waterbodySize = WaterBodySize;
    m_waterColor = waterColor;
    trianglesPerSide = static_cast<unsigned int>(m_waterbodySize/m_waveSize);

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

    for(int x = 0;x<trianglesPerSide-1;x++) {
        for (int z = 0; z < trianglesPerSide - 1; z++) {
            glm::vec3 main, sec, tri;
            //inject first triangle
            auto pos_in_vector = (x * trianglesPerSide) + z;
            main = rawVertices[pos_in_vector];
            sec = rawVertices[pos_in_vector + 1];
            tri = rawVertices[pos_in_vector + trianglesPerSide];

            //One Tiangle = (vec3posA,posab,posac,
            waterVertices.insert(waterVertices.end(), {main, sec, tri});
            waterVertices.insert(waterVertices.end(), {sec,tri, main});
            waterVertices.insert(waterVertices.end(), {tri, main, sec});
            //inject second triangle
            main = rawVertices[pos_in_vector + trianglesPerSide];
            sec = rawVertices[pos_in_vector + 1];
            tri = rawVertices[pos_in_vector + trianglesPerSide+1];
            waterVertices.insert(waterVertices.end(), {main, sec, tri});
            waterVertices.insert(waterVertices.end(), {sec,tri, main});
            waterVertices.insert(waterVertices.end(), {tri, main, sec});
        }
    }
    waterVertices.shrink_to_fit();

    PROGRAMM=essentials.loader.createProgram({{"water_vertex.glsl",ShaderLoader::VERTEX},
                                              {"water_fragment.glsl",ShaderLoader::FRAGMENT}});

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,waterVertices.size()*sizeof(glm::vec3),waterVertices.data(),GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(glm::vec3), (void*) sizeof(glm::vec3));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3*sizeof(glm::vec3), (void*)(2* sizeof(glm::vec3)));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);
}


