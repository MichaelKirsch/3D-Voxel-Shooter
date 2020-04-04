

#pragma once

#include "SFML/Graphics/Font.hpp"
#include <experimental/filesystem>
#include <unordered_map>


class FontLoader {
public:
    void loadFontFile(std::string& fontFile);




    ~FontLoader() = default;

private:
    sf::Font m_loadedFont;
protected:
};



