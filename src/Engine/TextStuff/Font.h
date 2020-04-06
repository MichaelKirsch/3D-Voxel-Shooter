#pragma once

#include "SFML/Graphics/Font.hpp"
#include <experimental/filesystem>

struct FontTexture
{
    sf::Image texture;
    int texture_size =0;
};

class Font {
public:
    Font()= default;
    void loadNewFont(std::string fontname, int textsize);
    FontTexture& getFont(int textSize);
    sf::Glyph getGlyph(char letter, int textsize);
    ~Font() = default;

private:
    std::string fontname = "";
    sf::Font m_font;
    const std::string m_charSet = "()[]{}<>!§$%&=?,.-;:_#*+~0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::map<int,FontTexture> loadedTextsizes;
protected:
};



