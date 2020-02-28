

#pragma once

#include "ShaderLoader.h"
class State {
public:
    State(ShaderLoader& loader) : sh_loader(loader){};
    ShaderLoader& sh_loader;
    virtual void updateFrame(){};
    virtual void updateEntities(){};
    virtual void processInputs(){};
    ~State()= default;
private:
protected:
};



