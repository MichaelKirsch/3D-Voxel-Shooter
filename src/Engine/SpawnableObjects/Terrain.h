

#pragma once

#include "Renderable.h"
#include "StateMachine/Essential.h"
#include "FastNoise/FastNoise.h"

class Terrain : public Renderable {
public:
    Terrain(StateEssentials& es,int seed=100, int size=100);

    void render() override;

    ~Terrain() = default;

private:
    void checkForCracks();
    StateEssentials& essential;
    unsigned int VAO,VBO,ProgrammID;
    std::vector<glm::vec3> positions;
    FastNoise noise;
protected:
};



