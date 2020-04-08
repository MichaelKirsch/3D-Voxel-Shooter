

#include "ImprovedTerrain.h"

ImprovedTerrain::~ImprovedTerrain() {
    PROGRAMM = ShaderLoader::createProgram({{"imp_terrain"}});
}

ImprovedTerrain::ImprovedTerrain() {

}

glm::vec3 ImprovedTerrain::convertVertexToDatastream(Vertex &vertex) {

    unsigned int color_and_sides;
    color_and_sides = vertex.color_red;
    color_and_sides = (color_and_sides<<8) + vertex.color_green;
    color_and_sides = (color_and_sides<<8) + vertex.color_blue;
    color_and_sides = (color_and_sides<<8) + vertex.active_sides;

    unsigned int position_1;
    position_1 = vertex.position_x;
    position_1 = (position_1<<16) + vertex.position_y;

    unsigned int position_2;
    position_2 = vertex.position_z;
    position_2 = (position_2<<16) + vertex._spare;

    float float1 = glm::uintBitsToFloat(color_and_sides);
    float float2 = glm::uintBitsToFloat(position_1);
    float float3 = glm::uintBitsToFloat(position_2);

    return glm::vec3(float1,float2,float3);
}

void ImprovedTerrain::render() {
}

void ImprovedTerrain::update(float &elapsed) {
}

void ImprovedTerrain::create() {
}




