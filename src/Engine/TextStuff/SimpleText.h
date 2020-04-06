#pragma once

#include "Essential.h"
#include "Font.h"
class SimpleText {
public:
    SimpleText(StateEssentials& es);
    void create(glm::vec2 topleft,Font* font, int textsize ,std::string text);
    void setText(std::string newText);
    void render();
    ~SimpleText() = default;

private:
    std::vector<float> vertices;
    unsigned int VAO,VBO, PROGRAMM, TEXTURE;
    StateEssentials* essentials;
    float cursorPosition;
    int textsize;
    FontTexture* ft;
    float baselinex,baseliney;
protected:
};



