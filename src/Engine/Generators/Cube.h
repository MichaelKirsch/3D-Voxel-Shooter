

#pragma once

#include "glm/glm/glm.hpp"
#include "Essential.h"
enum class CUBE_SIDES
{
    up=0,down,right,left,front,back,air_block,liquid_block
};

struct Cube
{
    glm::vec3 blockID_and_sides;
};


