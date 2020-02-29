

#pragma once

#include "SFML/Graphics.hpp"
#include "glad/glad.h"
#include <stdexcept>
#include "glm.hpp"

class WindowManager {
public:
    WindowManager();
    void create(sf::Vector2u resolution={1000,1000}, bool fullscreen= false, float fov = 60, float range = 500.f);
    void swapBuffers();
    void clearScreen();
    glm::mat4 perspectiveProjection;
    sf::Window& getWindow();
    ~WindowManager();

private:
    sf::Window m_Window;
protected:
};



