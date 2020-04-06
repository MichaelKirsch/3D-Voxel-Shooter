

#include "SimpleText.h"

void SimpleText::create(glm::vec2 topleft,Font* font, int txtsize, std::string text) {
    glGenTextures(1,&TEXTURE);
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    PROGRAMM = StateEssentials::get().loader.createProgram({{"text_vertex.glsl",ShaderLoader::VERTEX},
                                                 {"text_fragment.glsl",ShaderLoader::FRAGMENT}});



    baselinex = topleft.x;
    baseliney = topleft.y;
    vertices.clear();
    textsize = txtsize;
    m_font = font;
    auto sizeTexure = font->getFont(textsize).texture_size;

    cursorPosition = 0;
    sf::Vector2f posOnScreen = {baselinex,baseliney};
    vertices.clear();
    glBindTexture(GL_TEXTURE_2D, TEXTURE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,font->getFont(textsize).texture.getSize().x,
            font->getFont(textsize).texture.getSize().y,
            0,GL_RGBA, GL_UNSIGNED_BYTE, font->getFont(textsize).texture.getPixelsPtr());

    glGenerateMipmap(GL_TEXTURE_2D);

    setText(text);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5* sizeof(float),(void*)0); //position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5* sizeof(float),(void*)(3 * sizeof(float))); //textureCoordinates
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
}

SimpleText::SimpleText() {
}

void SimpleText::render() {
    StateEssentials::get().loader.useProgramm(PROGRAMM);
    StateEssentials::get().loader.setUniform(StateEssentials::get().windowManager.perspectiveProjection,"projection");
    StateEssentials::get().loader.setUniform(StateEssentials::get().camera.GetViewMatrix(),"view");
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D,TEXTURE);
    glDrawArrays(GL_TRIANGLES,0,vertices.size());
    glBindVertexArray(0);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glEnable(GL_CULL_FACE);
}

void SimpleText::setText(std::string newText) {
    sf::Vector2f posOnScreen = {baselinex,baseliney};
    vertices.clear();
    for(char letter:newText)
    {
        sf::Glyph tempGlyph = m_font->getGlyph(letter,textsize);
        int getTextureSize = m_font->getFont(textsize).texture.getSize().x;
        float percTexture =  1.f/getTextureSize;
        sf::Vector2f topLeftCalculated = {tempGlyph.textureRect.left*percTexture,(tempGlyph.textureRect.top*percTexture)};
        sf::Vector2f widthHeightCalculated = {tempGlyph.textureRect.width*percTexture,tempGlyph.textureRect.height*percTexture};
        auto adjustedAdvance = (1.0f/StateEssentials::get().windowManager.getWindow().getSize().x)*tempGlyph.advance;

        auto adjustedheight = (1.0f/StateEssentials::get().windowManager.getWindow().getSize().y)*tempGlyph.bounds.height;
        auto adjustedwidth = (1.0f/StateEssentials::get().windowManager.getWindow().getSize().x)*tempGlyph.bounds.width;
        auto adjustedtop = (1.0f/StateEssentials::get().windowManager.getWindow().getSize().y)*tempGlyph.bounds.top;


        std::vector<float> temp = {
                // positions          // texture coords
                posOnScreen.x,  adjustedheight+posOnScreen.y, 0.0f,   topLeftCalculated.x, topLeftCalculated.y,    // top left
                posOnScreen.x, posOnScreen.y, 0.0f,   topLeftCalculated.x, topLeftCalculated.y+widthHeightCalculated.y,   // bottom left
                adjustedwidth+posOnScreen.x,posOnScreen.y, 0.0f,   topLeftCalculated.x+widthHeightCalculated.x, topLeftCalculated.y+widthHeightCalculated.y,   // bottom right
                adjustedwidth+posOnScreen.x,posOnScreen.y, 0.0f,   topLeftCalculated.x+widthHeightCalculated.x, topLeftCalculated.y+widthHeightCalculated.y,   // bottom right
                adjustedwidth+posOnScreen.x, adjustedheight+posOnScreen.y, 0.0f,   topLeftCalculated.x+widthHeightCalculated.x, topLeftCalculated.y,   // top right
                posOnScreen.x,adjustedheight+posOnScreen.y, 0.0f,  topLeftCalculated.x, topLeftCalculated.y   // top left
        };
        vertices.insert(vertices.end(),temp.begin(),temp.end());
        posOnScreen.x+=adjustedAdvance;
    }
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,vertices.size()* sizeof(float),vertices.data(),GL_STATIC_DRAW);
    glBindVertexArray(0);
}
