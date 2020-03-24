

#pragma once

#include "Renderable.h"
#include "StateMachine/Essential.h"
class Skybox : public Renderable {
public:
    Skybox(StateEssentials& es, glm::vec3 gradientColorLow, glm::vec3 gradientColorHigh);

    void render() override;

    void update(float &elapsed) override;

    void create() override;

    ~Skybox() = default;

private:
    unsigned int VAO, VBO, PROGRAMM;
protected:
};



