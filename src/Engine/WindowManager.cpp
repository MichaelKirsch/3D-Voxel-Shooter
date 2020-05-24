

#include <glm/glm/gtc/matrix_transform.hpp>
#include "WindowManager.h"

WindowManager::~WindowManager() {
    m_Window.close();
}

void WindowManager::swapBuffers() {
    m_Window.display();
}

sf::Window &WindowManager::getWindow() {
    return m_Window;
}

void WindowManager::clearScreen() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

WindowManager::WindowManager() {

}

void WindowManager::create(sf::Vector2u resolution , bool fullscreen,float fov, float range) {
    clearColor = {0, 0.874, 1,1.0};
    sf::ContextSettings settings;
    m_range = range;
    m_fov = fov;
    m_fullscreen = fullscreen;

    perspectiveProjection = glm::perspective(glm::radians(fov), (float)resolution.x/(float)resolution.y, 0.1f, range);
    settings.depthBits = 24;
    settings.attributeFlags = settings.Core;
    settings.antialiasingLevel = 4;
    settings.minorVersion = 3;
    settings.majorVersion = 4;
    if(!fullscreen)
        m_Window.create(sf::VideoMode(resolution.x,resolution.y),"TopDown", sf::Style::Default, settings);
    else
        m_Window.create(sf::VideoMode::getDesktopMode(),"TopDown", sf::Style::Fullscreen , settings);

    m_Window.setActive();
    if(!gladLoadGL())
    {
        throw std::runtime_error("Glad is not loading");
    }
    glViewport(0, 0, m_Window.getSize().x,m_Window.getSize().y);
    glClearColor(clearColor.x,clearColor.y,clearColor.z,clearColor.a);
    glEnable(GL_DEPTH_TEST);
}

void WindowManager::setRange(float newrange) {
    m_range = newrange;
    refactorProjection();
}

void WindowManager::refactorProjection() {
    perspectiveProjection = glm::perspective(glm::radians(m_fov), (float)m_resolution.x/(float)m_resolution.y, 0.1f, m_range);
}

void WindowManager::setClearColor(glm::vec4 color) {
    clearColor = color;
    glClearColor(color.x,color.y,color.z,1.0);
}


