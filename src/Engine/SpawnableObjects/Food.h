

#pragma once

#include "Renderable.h"
#include "StateMachine/Essential.h"
#include "Terrain.h"
#include "FastNoise/FastNoise.h"

struct Berry
{
    glm::vec3 position;
    glm::vec3 color;
};

class Food : public Renderable {
public:
    Food(StateEssentials& es);

    void render() override;

    void update(float &elapsed) override;

    void create(Terrain& ter,int amount, float respawntime);

    ~Food() = default;

private:
    glm::mat4 model;
    unsigned int VAO,VBO,PROGRAMM;
    StateEssentials& stateEssentials;
    std::vector<Berry> berries;
protected:
};



