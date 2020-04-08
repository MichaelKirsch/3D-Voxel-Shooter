

#include "ImprovedTerrain.h"

ImprovedTerrain::ImprovedTerrain() {
    PROGRAMM = ShaderLoader::createProgram({{"imp_terrain.vert"},{"imp_terrain.frag"}});
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);
}

ImprovedTerrain::~ImprovedTerrain() {
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
}

void ImprovedTerrain::create(unsigned int i_size, float i_freq, float border) {
    m_size = i_size;
    m_noise.SetFrequency(i_freq);
    m_noise.SetNoiseType(FastNoise::Simplex);
    for(int x =0;x<i_size;x++)
    {
        for(int z=0;z<i_size;z++)
        {
            auto meshes = generateMeshDownwardsThisPoint(x, z);
            for(auto mesh:meshes)
            {
                m_VertexData.push_back(convertMeshToVec3(mesh));
            }
        }
    }
}

void ImprovedTerrain::render() {
}

void ImprovedTerrain::update(float &elapsed) {
}

glm::vec3 ImprovedTerrain::convertMeshToVec3(Vertex &vertex) {

    unsigned int color_and_sides;
    color_and_sides = vertex.color_red;
    color_and_sides = (color_and_sides<<8) + vertex.color_green;
    color_and_sides = (color_and_sides<<8) + vertex.color_blue;
    color_and_sides = (color_and_sides<<8) + vertex.normal;

    unsigned int position_1;
    position_1 = vertex.center_x;
    position_1 = (position_1<<16) + vertex.center_y;

    unsigned int position_2;
    position_2 = vertex.center_z;
    position_2 = (position_2<<8) + vertex.which_vertex;
    position_2 = (position_2<<8) + vertex._spare;

    float float1 = glm::uintBitsToFloat(color_and_sides);
    float float2 = glm::uintBitsToFloat(position_1);
    float float3 = glm::uintBitsToFloat(position_2);

    return glm::vec3(float1,float2,float3);
}

std::vector<Vertex> ImprovedTerrain::generateMeshDownwardsThisPoint(int x, int z) {
    std::vector<Vertex> buf;
    auto starting_height_pillar = getHeightOfTerrain(x,z);
    for(int y =0;y<=starting_height_pillar;y++)
    {
        auto t = generateMeshOfSingleBlock(x,y,z);
        buf.insert(buf.end(),t.begin(),t.end());
    }
    return buf;
}

int ImprovedTerrain::getHeightOfTerrain(int x, int z) {
    auto raw_noise =  m_noise.GetNoise(x,z);
    raw_noise+=1.f;
    raw_noise/=2.f;
    return (int)(raw_noise*max_terrain_height);
}

std::bitset<6> ImprovedTerrain::determineBlockVisibility(int x,int y, int z) {
    std::bitset<6> buf;
    bool active;
    buf.reset();
    active = (getHeightOfTerrain(x-1,z)<y);
    buf.set(left,active); //left
    active = (getHeightOfTerrain(x+1,z)<y);
    buf.set(right,active); //right
    active = (getHeightOfTerrain(x,z-1)<y);
    buf.set(back,active); //back
    active = (getHeightOfTerrain(x,z+1)<y);
    buf.set(front,active); //front
    active = (getHeightOfTerrain(x,z)==y);
    buf.set(up,active); //up only set when
    buf.set(down,false); //future proof

    return buf;
}

std::vector<Vertex> ImprovedTerrain::generateMeshOfSingleBlock(int x, int y, int z) {

    std::vector<Vertex> buf;

    auto which_sides_to_make = determineBlockVisibility(x,y,z);

    if(!which_sides_to_make.none())
    {
        if(which_sides_to_make.test(front))
        {
            auto t = generateSide({x,y,z},front,{0,1,2,0,2,3});
            buf.insert(buf.end(),t.begin(),t.end());
        }
        if(which_sides_to_make.test(back))
        {
            auto t = generateSide({x,y,z},back,{5,7,6,5,4,7});
            buf.insert(buf.end(),t.begin(),t.end());
        }
        if(which_sides_to_make.test(left))
        {
            auto t = generateSide({x,y,z},left,{0,3,7,0,7,4});
            buf.insert(buf.end(),t.begin(),t.end());
        }
        if(which_sides_to_make.test(right))
        {
            auto t = generateSide({x,y,z},right,{5,6,2,5,2,1});
            buf.insert(buf.end(),t.begin(),t.end());
        }
        if(which_sides_to_make.test(up))
        {
            auto t = generateSide({x,y,z},up,{3,2,7,2,6,7});
            buf.insert(buf.end(),t.begin(),t.end());
        }
        if(which_sides_to_make.test(down))
        {
            auto t = generateSide({x,y,z},down,{1,5,0,5,4,0});
            buf.insert(buf.end(),t.begin(),t.end());
        }
    }

    return buf;
}

std::vector<Vertex> ImprovedTerrain::generateSide(glm::vec3 center, sides side, std::vector<int> order) {
    std::vector<Vertex> buf;

    Vertex bufferVertex;
    bufferVertex.center_x = center.x;
    bufferVertex.center_y = center.y;
    bufferVertex.center_z = center.z;
    bufferVertex.normal = side;

    for(auto which:order)
    {
        bufferVertex.which_vertex = which;
        buf.push_back(bufferVertex);
    }
    return buf;
}






