

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
    sf::ContextSettings settings;
    m_range = range;
    m_fov = fov;
    m_fullscreen = fullscreen;
    perspectiveProjection = glm::perspective(glm::radians(fov), (float)resolution.x/(float)resolution.y, 0.1f, range);
    settings.depthBits = 8;
    settings.antialiasingLevel = 4;
    settings.minorVersion = 3;
    settings.majorVersion = 4;
    if(!fullscreen)
        m_Window.create(sf::VideoMode(resolution.x,resolution.y),"Pushy", sf::Style::Default, settings);
    else
        m_Window.create(sf::VideoMode(resolution.x,resolution.y),"Pushy", sf::Style::Fullscreen , settings);

    m_Window.setActive();
    if(!gladLoadGL())
    {
        std::runtime_error("Glad is not loading");
    }
    glViewport(0, 0, m_Window.getSize().x,m_Window.getSize().y);
    glClearColor(0.027f, 0.7f, 0.9f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

void WindowManager::setRange(float newrange) {
    m_range = newrange;
    refactorProjection();
}

void WindowManager::refactorProjection() {
    perspectiveProjection = glm::perspective(glm::radians(m_fov), (float)m_resolution.x/(float)m_resolution.y, 0.1f, m_range);
}


