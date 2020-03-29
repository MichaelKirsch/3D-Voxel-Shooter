

#include "TerrainGenerator.h"

TerrainGenerator::TerrainGenerator(StateEssentials &es) : stateEssentials(es) {

}

void TerrainGenerator::setUpGenerator(glm::ivec3 origin_offset, float freqency, int terrain_height,
                                      FastNoise::NoiseType noiseType) {
    m_noise.SetFrequency(freqency);
    m_noise.SetNoiseType(noiseType);
    m_maxTerrainHeight = terrain_height;
}


bool TerrainGenerator::generateCube(glm::ivec3 &position, Cube &cube,glm::ivec3& positionInChunk) {
    auto terrainHeightAtThisPos = getTerrain(position.x,position.z);

    cube_pos_and_sides cubeEssential;


    if(terrainHeightAtThisPos<=position.y) //cube is under or on Terrain
    {
        if(terrainHeightAtThisPos==position.y)
        {
            //cube is the terrain, so we will need the top side;
            setFace(cubeEssential.activeSides,CUBE_SIDES::up);
        }
        if(sideNeeded({-1,0,0},position))
            setFace(cubeEssential.activeSides,CUBE_SIDES::left);
        if(sideNeeded({1,0,0},position))
            setFace(cubeEssential.activeSides,CUBE_SIDES::right);
        if(sideNeeded({0,0,-1},position))
            setFace(cubeEssential.activeSides,CUBE_SIDES::back);
        if(sideNeeded({0,0,1},position))
            setFace(cubeEssential.activeSides,CUBE_SIDES::front);
        //im not having overhangs atm so lets not check that
        //if(sideNeeded({0,-1,0},position))
        //    setFace(cubeEssential.activeSides,CUBE_SIDES::down);
        if(cubeEssential.activeSides==0)
            return false; //burried block

        //lets bitshift all the information into the cubes float
        unsigned int bufferCubeInfo = glm::uint8(positionInChunk.x);
        bufferCubeInfo = (bufferCubeInfo<<8)+glm::uint8(positionInChunk.y);
        bufferCubeInfo = (bufferCubeInfo<<8)+glm::uint8(positionInChunk.z);
        bufferCubeInfo = (bufferCubeInfo<<8)+cubeEssential.activeSides;
        //we encode everything in float as GPUs like floats
        cube.position_and_sides = glm::uintBitsToFloat(bufferCubeInfo);
        return true;
    }
    return false; //airblock
}



bool TerrainGenerator::sideNeeded(glm::ivec3 offset, glm::ivec3 &position) {
    return getTerrain(position.x + offset.x, position.z + offset.z) < position.y;
}



int TerrainGenerator::getTerrain(int x, int y) {
    return static_cast<int>(m_noise.GetNoise(static_cast<FN_DECIMAL>(x), static_cast<FN_DECIMAL>(y)) * m_maxTerrainHeight);
}


void TerrainGenerator::setFace(glm::uint8 &var, CUBE_SIDES face, bool status) {
    if (status)
        var |= (1 << (GLubyte) face);
    else
        var &= ~(1 << (GLubyte) face);
}




