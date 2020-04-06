

#include "Font.h"

void Font::loadNewFont(std::string name, int textsize) {
    fontname = name;
    std::string path_to_font_dir = std::experimental::filesystem::current_path().parent_path().string();
    path_to_font_dir +="/data/fonts/";
    if(!m_font.loadFromFile(path_to_font_dir + fontname))
        throw std::runtime_error("Font "+ fontname + " cant be loaded.");

    //lets generate the font texure with all the chars in our charset
    for(char letter:m_charSet)
    {
        m_font.getGlyph(letter,textsize,false);
    }
    const sf::Texture& temp = m_font.getTexture(textsize);
    FontTexture ft;
    ft.texture = temp.copyToImage();
    ft.texture_size = ft.texture.getSize().x;
    loadedTextsizes.insert(std::make_pair(textsize,ft));
}

FontTexture &Font::getFont(int textSize) {
    if(fontname=="")
        throw std::runtime_error("Font not initialiced");
    if(loadedTextsizes.find(textSize)==loadedTextsizes.end())
    {
        loadNewFont(fontname,textSize);
    }
    return loadedTextsizes.at(textSize);
}

sf::Glyph Font::getGlyph(char letter, int textsize) {
    return m_font.getGlyph(letter,textsize, false);
}
