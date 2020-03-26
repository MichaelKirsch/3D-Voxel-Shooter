

#pragma once

#include "glm/glm/glm.hpp"

enum class CUBE_SIDES
{
    up=0,down,right,left,front,back,air_block,liquid_block
};

struct CubeGraphicData
{
    glm::u8vec3 position; //only 8 bits needed because its in a chunk
    glm::uint16 blockID;
    glm::uint8 activeFaces=0;
};

struct Cube
{
    CubeGraphicData data;
};


