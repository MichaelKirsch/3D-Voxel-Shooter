

#pragma once

#include "SFML/Graphics.hpp"
#include "glad/glad.h"
#include <stdexcept>

class WindowManager {
public:
    WindowManager(sf::Vector2i resolution, bool fullscreen);
    void swapBuffers();
    sf::Window& getWindow();
    ~WindowManager();

private:
    sf::Window m_Window;
protected:
};



