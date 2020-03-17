

#pragma once

#include "Renderable.h"
#include "StateMachine/Essential.h"
#include "FastNoise/FastNoise.h"

class Terrain : public Renderable {
public:
    Terrain(StateEssentials& es,int seed=100, int size=300);

    void render() override;

    ~Terrain() = default;

private:
    float calculateBorderFactor(float x , float y, int size,float border_thiccccness=.2);
    void checkForCracks();
    StateEssentials& essential;
    unsigned int VAO,VBO,ProgrammID;
    std::vector<glm::vec3> positions;
    FastNoise noise;
protected:
};



