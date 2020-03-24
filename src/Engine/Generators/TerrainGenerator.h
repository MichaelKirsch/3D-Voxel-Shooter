//this class can be consultated mainly by chunk or other classes to get terrain information about a certain point in the world.
//using this class will ensure that everything will get generated uniformly. This class can be used to say where water should be
//generated too. the watergenerator and the wildlifePlantGenerator will be heavyly dependent on this class.
//set this generator once and then use it throuout your code

#pragma once

#include "StateMachine/Essential.h"
#include "FastNoise/FastNoise.h"
#include "Cube.h"
class TerrainGenerator {
public:
    TerrainGenerator(StateEssentials& es);
    void setUpGenerator(glm::ivec3 origin_offset= {0,0,0},float freqency=0.015f, FastNoise::NoiseType noiseType = FastNoise::Simplex);
    void getCubeAtPosition(glm::ivec3& position, Cube& cube);
    ~TerrainGenerator() = default;
    void setFace(Cube& cube, CUBE_SIDES face,bool status=true);
    int getTerrain(int x, int y);
private:
    StateEssentials& stateEssentials;
    FastNoise m_noise;
    bool sideNeeded(glm::ivec3 offset,glm::ivec3& position);
protected:
};



