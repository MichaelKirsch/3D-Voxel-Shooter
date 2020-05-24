#include "ProjectileGenerator.h"

void ProjectileGenerator::render() {
    ShaderLoader::useProgramm(PROGRAMM);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, m_gpudata.size()*sizeof(float), m_gpudata.data(),
                 GL_DYNAMIC_DRAW);
    ShaderLoader::setUniform(PROGRAMM,StateEssentials::get().camera.GetViewMatrix(),"view");
    ShaderLoader::setUniform(PROGRAMM,StateEssentials::get().camera.Position,"cameraPos");
    ShaderLoader::setUniform(PROGRAMM,StateEssentials::get().windowManager.perspectiveProjection,"projection");
    glDrawArrays(GL_POINTS, 0, m_gpudata.size()/7);
    glBindVertexArray(0);
}

void ProjectileGenerator::update() {
    m_gpudata.clear();
    float elapsed = m_clock.restart().asSeconds();

    for(auto& pr:m_projectiles)
    {
        pr->update(elapsed);
        m_gpudata.push_back(pr->m_size);
        m_gpudata.push_back(pr->m_position.x);
        m_gpudata.push_back(pr->m_position.y);
        m_gpudata.push_back(pr->m_position.z);
        m_gpudata.push_back(pr->m_direction.x);
        m_gpudata.push_back(pr->m_direction.y);
        m_gpudata.push_back(pr->m_direction.z);
    }
    for(auto it = std::begin(m_projectiles); it != std::end(m_projectiles); ) {
        auto& pr = *it;
        // ...
        if(!pr->alife) {
            it = m_projectiles.erase(it);
        } else {
            ++it;
        }
    }
}

void ProjectileGenerator::create(ImprovedTerrain* ter,std::string frag, std::string vert,std::string geom) {
    PROGRAMM = ShaderLoader::createProgram({frag,vert,geom});
    m_ter = ter;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)sizeof(glm::vec4));
    glBindVertexArray(0);
}

bool ProjectileGenerator::checkHitbox(Hitbox *toCheck) {
    for(auto& z:m_projectiles)
        if(toCheck->collisionDetectionPoint(z->m_position))
            return true;
    return false;
}


