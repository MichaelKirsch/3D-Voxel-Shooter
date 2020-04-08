

#include "Water.h"

Water::Water(){
}

void Water::render() {
    ShaderLoader::useProgramm(PROGRAMM);
    ShaderLoader::setUniform(PROGRAMM,m_waterColor,"WaterColor");
    ShaderLoader::setUniform(PROGRAMM,StateEssentials::get().windowManager.perspectiveProjection,"projection");
    ShaderLoader::setUniform(PROGRAMM,StateEssentials::get().camera.GetViewMatrix(),"view");
    ShaderLoader::setUniform(PROGRAMM,m_degrees,"degrees");
    ShaderLoader::setUniform(PROGRAMM,m_waveheight,"waveheight");
    ShaderLoader::setUniform(PROGRAMM,StateEssentials::get().camera.Position,"cameraPos");
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES,0,waterVertices.size()/3);
    glBindVertexArray(1);
}

void Water::update(float& elapsed) {
    m_degrees+=m_speed;
}

void Water::create(Terrain& ter,glm::vec3 origin, float WaveSize, float WaterBodySize, glm::vec3 waterColor, float speed,float waveheight,float freq) {
    m_origin = origin;
    m_waveheight = waveheight;
    m_waveSize = WaveSize;
    m_speed = speed;
    m_freq = freq;
    noise.SetNoiseType(FastNoise::Simplex);
    noise.SetFrequency(freq);
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
            glm::vec3 rawPos = {(float)x*m_waveSize,y,(float)z*m_waveSize};
            rawPos+=m_origin;
            rawVertices.emplace_back(rawPos);
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

    PROGRAMM=ShaderLoader::createProgram({{"water.vert"},{"water.frag"}});

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

Water::~Water() {
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&VAO);
    glDeleteProgram(PROGRAMM);
}



