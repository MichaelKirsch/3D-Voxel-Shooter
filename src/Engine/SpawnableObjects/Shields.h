

#pragma once

#include "Renderable.h"
#include "Hitbox.h"

class Shields : public Renderable {
public:

    enum shield_type
    {
        light,medium,heavy
    };

    Shields();

    void render() override;

    void update(float &elapsed) override;

    void create(glm::vec3 origin, shield_type type);

    bool taken;

    ~Shields() = default;

    Hitbox hitbox;

private:
protected:
};



