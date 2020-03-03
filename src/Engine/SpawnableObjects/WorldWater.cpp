

#include "WorldWater.h"

WorldWater::WorldWater(StateEssentials& es,unsigned int size, int seed) : essentials(es) {
    m_size = size;
    m_noise.SetNoiseType(FastNoise::SimplexFractal);
    m_noise.SetFrequency(10.f);
    //m_noise.SetSeed(seed);
    PROG = essentials.loader.createProgram({{"water_fragment.glsl",ShaderLoader::FRAGMENT},
                                 {"water_vertex.glsl",ShaderLoader::VERTEX}});
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
    waveheight  = 0.4f;
    glGenBuffers(1,&EBO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&NORMALS);

    for(int x =0;x<size;x++)
    {
        for(int z =0;z<size;z++)
        {
            float y=m_noise.GetNoise(x,z);
            y+=1.0f;
            y/=2.f;
            positions.emplace_back(glm::vec3(x,y,z));
        }
    }

    glGenBuffers(1,&VBO);
    glBufferData(GL_ARRAY_BUFFER, positions.size()* sizeof(glm::vec3),&positions[0], GL_STATIC_DRAW);
    generateElements();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size()*sizeof(unsigned int), &elements[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, NORMALS);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glVertexAttribDivisor(1, 1);
    glEnableVertexAttribArray(1);
    normals.resize(elements.size());
    std::fill(normals.begin(),normals.end(),glm::vec3(1.f,0.f,0.f));
    update(0.f);
    glBindBuffer(GL_ARRAY_BUFFER,NORMALS);
    glBufferData(GL_ARRAY_BUFFER,normals.size()*sizeof(glm::vec3),&normals[0],GL_STATIC_DRAW);
    glBindVertexArray(0);
}

void WorldWater::render() {
    essentials.loader.useProgramm(PROG);
    essentials.loader.setUniform(model,"model");
    essentials.loader.setUniform(essentials.camera.GetViewMatrix(),"view");
    essentials.loader.setUniform(essentials.windowManager.perspectiveProjection,"projection");
    essentials.loader.setUniform(essentials.camera.Position,"viewPos");
    essentials.loader.setUniform(waveheight,"waveheight");
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES,elements.size(),GL_UNSIGNED_INT,0);
    glBindVertexArray(0);
}

void WorldWater::update(float change) {
    for(auto& points:positions)
    {
        points.y+=change;
        if(points.y>1.0f)
            points.y =0.f;
    }

    for(int iterate =0;iterate<elements.size();iterate+=3)
    {
        int position_in_elements = iterate;

        glm::vec3 point1 = positions[elements[position_in_elements]];
        glm::vec3 point2 = positions[elements[position_in_elements+1]];
        glm::vec3 point3 = positions[elements[position_in_elements+2]];
        point1.y =sin(point1.y*2*M_PI)*waveheight;
        point2.y =sin(point2.y*2*M_PI)*waveheight;
        point2.y =sin(point2.y*2*M_PI)*waveheight;
        glm::vec3 rv1=(point1-point2);
        glm::vec3 rv2 =(point1-point3);
        normals[iterate] = glm::normalize(glm::cross(rv1,rv2));
        normals[iterate+1] = glm::normalize(glm::cross(rv1,rv2));
        normals[iterate+2] =glm::normalize(glm::cross(rv1,rv2));
    }
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3),&positions[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ARRAY_BUFFER, NORMALS);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3),&normals[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
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
            elements.emplace_back(pos_in_vector+m_size);
            elements.emplace_back(pos_in_vector+1);
            elements.emplace_back(pos_in_vector+m_size+1);
        }
    }
}
