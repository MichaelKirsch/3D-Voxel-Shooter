

#include "TerrainGenerator.h"



void TerrainGenerator::getCubeAtPosition(glm::ivec3 &position, Cube &cube ) {
    auto getTerrainHeight = getTerrain(position.x,position.z);
    if(getTerrainHeight == position.y)
    {
        //when the block is terrain then we can for sure set the top active
        setFace(cube,CUBE_SIDES::up);
        cube.data.blockID = 1;
    }
    else if(getTerrainHeight <=position.y)
        cube.data.blockID = 2;
    else
    {
        cube.data.blockID = 0;
        setFace(cube,CUBE_SIDES::air_block);
        //it is an airblock, so all values will be zero
        return;
    }
    if(sideNeeded({1,0,0},position))
    {
        setFace(cube,CUBE_SIDES::right);
    }
    if(sideNeeded({-1,0,0},position))
    {
        setFace(cube,CUBE_SIDES::left);
    }
    if(sideNeeded({0,1,0},position))
    {
        setFace(cube,CUBE_SIDES::front);
    }
    if(sideNeeded({0,-1,0},position))
    {
        setFace(cube,CUBE_SIDES::back);
    }
}

void TerrainGenerator::setUpGenerator(glm::ivec3 origin_offset, float freqency, FastNoise::NoiseType noiseType) {
    m_noise.SetFrequency(freqency);
    m_noise.SetNoiseType(noiseType);
}

void TerrainGenerator::setFace(Cube &cube, CUBE_SIDES face, bool status) {
    if(status)
        cube.data.activeFaces |= (1<<(glm::uint8)face);
    else
        cube.data.activeFaces &= ~(1<<(glm::uint8)face);
}

bool TerrainGenerator::sideNeeded(glm::ivec3 offset, glm::ivec3 &position) {
    auto get_terrain_at_check_pos = getTerrain(position.x+offset.x,position.z+offset.z);
    if(get_terrain_at_check_pos<position.y)
        return true;
    //when the next block is under the current block we will need a side
    return false;
}

TerrainGenerator::TerrainGenerator(StateEssentials &es) : stateEssentials(es) {

}

int TerrainGenerator::getTerrain(int x, int y) {
    return static_cast<int>(m_noise.GetNoise(x,y)*15.f);
}
