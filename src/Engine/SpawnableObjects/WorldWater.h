

#pragma once

#include "glad/glad.h"
#include "FastNoise/FastNoise.h"
#include "Renderable.h"
#include "StateMachine/Essential.h"
#include <vector>
#include <cmath>
#include "glm.hpp"
class WorldWater : public Renderable {
public:
    WorldWater(StateEssentials& es,unsigned int size=200, int seed=100);
    void update(float angle);
    void render() override;
    ~WorldWater() = default;

private:
    glm::mat4 model = glm::mat4(1.0f);
    FastNoise m_noise;
    StateEssentials& essentials;
    unsigned int VAO,EBO,VBO,PROG,NORMALS;
    unsigned int m_size;
    void generateElements();
    std::vector<unsigned int> elements;
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
protected:
};



