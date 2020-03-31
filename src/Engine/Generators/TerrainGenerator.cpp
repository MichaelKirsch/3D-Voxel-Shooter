#include "TerrainGenerator.h"

void TerrainGenerator::setUpGenerator(float freqency, int terrain_height,
                                      FastNoise::NoiseType noiseType) {
    m_noise.SetFrequency(freqency);
    m_noise.SetNoiseType(noiseType);
    m_maxTerrainHeight = terrain_height;
    glPointSize(3);
}

bool TerrainGenerator::sideNeeded(int x_offset,int z_offset, glm::ivec3 &position, int& ownheight) {
    return (getTerrain(position.x + x_offset, position.z + z_offset) < ownheight);
}



int TerrainGenerator::getTerrain(int x, int y) {
    return static_cast<int>(m_noise.GetNoise(static_cast<FN_DECIMAL>(x), static_cast<FN_DECIMAL>(y)) * m_maxTerrainHeight)+m_maxTerrainHeight*0.6;
}


void TerrainGenerator::setFace(glm::uint8 &var, CUBE_SIDES face, bool status) {

    std::bitset<8>bits{var};
    bits.set(face,status);
    var =(glm::uint8)(bits.to_ulong());
}

std::vector<Cube> TerrainGenerator::generateCubesBelow(glm::ivec3 &chunkPosition, glm::ivec3 &positionInChunk, int& chunksize) {
    //find out if the block is even close to being with terrain
    auto zero = glm::ivec3(chunkPosition*chunksize);
    cube_pos_and_sides cubeEssential;
    auto max_height = zero.y + chunksize;
    auto position_worldSpace = glm::ivec3(zero+positionInChunk);
    auto terrain_height_at_pos = getTerrain(position_worldSpace.x,position_worldSpace.z);
    std::vector<Cube> to_return;
    if(terrain_height_at_pos<max_height && terrain_height_at_pos>zero.y)
    {
        //terrain seems to be in this collum
        auto height_in_chunk = terrain_height_at_pos%chunksize;
        Cube cube;
        //cube is the terrain, so we will need the top side;
        setFace(cubeEssential.activeSides,CUBE_SIDES::up);

        if(sideNeeded(-1,0,position_worldSpace,terrain_height_at_pos))
        {
            setFace(cubeEssential.activeSides,CUBE_SIDES::left);
        }
        if(sideNeeded(1,0,position_worldSpace,terrain_height_at_pos))
        {
            setFace(cubeEssential.activeSides,CUBE_SIDES::right);
        }
        if(sideNeeded(0,1,position_worldSpace,terrain_height_at_pos))
        {
            setFace(cubeEssential.activeSides,CUBE_SIDES::back);
        }

        if(sideNeeded(0,-1,position_worldSpace,terrain_height_at_pos))
        {
            setFace(cubeEssential.activeSides,CUBE_SIDES::front);
        }

        setFace(cubeEssential.activeSides,CUBE_SIDES::free_slot1,0);
        setFace(cubeEssential.activeSides,CUBE_SIDES::free_slot2,0);

        unsigned int bufferCubeInfo = glm::uint8(positionInChunk.x);
        bufferCubeInfo = (bufferCubeInfo<<8)+glm::uint8(height_in_chunk);
        bufferCubeInfo = (bufferCubeInfo<<8)+glm::uint8(positionInChunk.z);
        bufferCubeInfo = (bufferCubeInfo<<8)+glm::uint8(cubeEssential.activeSides);
        //we encode everything in float as GPUs like floats
        cube.position_and_sides = glm::uintBitsToFloat(bufferCubeInfo);
        //for now we will just return the same id everytime
        cube.blockID = glm::uintBitsToFloat(1);
        to_return.emplace_back(cube);
        return to_return;
        //iterate over all blocks below the surface Block and check for the sides that need to be rendered
    }
}






