

#pragma once

#include "glad/glad.h"
#include "FastNoise/FastNoise.h"
#include "Renderable.h"
#include "ShaderLoader.h"
#include <vector>
#include <cmath>
#include "glm.hpp"
class WorldWater : public Renderable {
public:
    WorldWater(ShaderLoader& loader,unsigned int size=200, int seed=100);
    void update(float angle);
    void render() override;
    ~WorldWater() = default;

private:
    FastNoise m_noise;
    ShaderLoader& m_loader;
    unsigned int VAO,EBO,VBO,PROG;
    unsigned int m_size;
    void generateElements();
    std::vector<unsigned int> elements;
    std::vector<glm::vec3> positions;
protected:
};



