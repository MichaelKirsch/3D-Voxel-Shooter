

#pragma once

#include "Renderable.h"
#include "SFML/Graphics.hpp"
#include <experimental/filesystem>
#include <map>
#include <unordered_map>
#include <Essential.h>

class TextBox : public Renderable{
public:
    TextBox()= default;

    void render() override;

    void update(float &elapsed) override;

    void create(StateEssentials& es,std::string fontname);

    ~TextBox() = default;

private:
    StateEssentials* stateEssentials;
    std::string path_to_fonts;
    sf::Font m_font;
    sf::Image m_Texture;
    std::unordered_map<int, sf::Texture> m_textures;
    const std::string m_charSet = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.,!?-+/()[]:;%&`*#=\"";
    unsigned int VAO,VBO,PROGRAM,IBO,texturePtr;
    const int textsize = 48;
protected:
};



