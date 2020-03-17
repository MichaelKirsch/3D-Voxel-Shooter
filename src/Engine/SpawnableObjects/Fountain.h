

#pragma once

#include "Renderable.h"
class Fountain :public Renderable{
public:
    Fountain();

    void render() override;

    void update(float &elapsed) override;

    ~Fountain() = default;

private:
protected:
};



