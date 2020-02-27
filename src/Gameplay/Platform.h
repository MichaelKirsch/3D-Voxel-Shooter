

#pragma once

#include "glm.hpp"
#include <vector>

class Platform {
public:
    Platform(unsigned int size, glm::vec3 origin);
    void draw();
    ~Platform() = default;
private:
    std::vector<glm::vec4> blocks;
protected:
};



