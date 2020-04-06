#pragma once

#include "Essential.h"
#include "Font.h"
class SimpleText {
public:
    SimpleText();
    void create(glm::vec2 topleft,Font* font, int textsize ,std::string text);
    void setText(std::string newText);
    void render();
    std::vector<float> generateSingleGlyphMesh();
    ~SimpleText() = default;

private:
    std::vector<float> vertices;
    unsigned int VAO,VBO, PROGRAMM, TEXTURE;
    float cursorPosition;
    int textsize;
    FontTexture* ft;
    Font* m_font;
    float baselinex,baseliney;
protected:
};



