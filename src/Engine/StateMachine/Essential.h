

#pragma once

#include "WindowManager.h"
#include "ShaderLoader.h"
#include "Camera.h"

//this is a big singleton that will serve as a base for all the other parts

class StateEssentials {
public:
    //StateEssentials(const StateEssentials&) = delete;
    WindowManager windowManager;
    Camera camera;

    static StateEssentials &get() {
        return s_Instance;
    }

    bool shouldClose; //temporary
private:
    StateEssentials() {};
    static StateEssentials s_Instance;
};




