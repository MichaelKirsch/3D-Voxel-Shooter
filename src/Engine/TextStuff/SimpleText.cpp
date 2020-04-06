

#include "SimpleText.h"

void SimpleText::create(glm::vec2 topleft,Font* font, int textsize, std::string text) {
    baselinex = topleft.x;
    baseliney = topleft.y;
    vertices.clear();
    auto sizeTexure = font->getFont(textsize).texture_size;
    //1*2
    //*/*
    //3*4

    //lets generate the vertices for every glyph
    //indicdes are 1,2,4,4,3,1
    cursorPosition = 0;
    auto letter = 'H';

    sf::Glyph tempGlyph = font->getGlyph(letter,textsize);
    std::cout << tempGlyph.textureRect.top << "|" << tempGlyph.textureRect.left << std::endl;
    int getTextureSize = font->getFont(60).texture.getSize().x;
    float percTexture =  1.f/getTextureSize;
    sf::Vector2f topLeftCalculated = {tempGlyph.textureRect.left*percTexture,(tempGlyph.textureRect.top*percTexture)};
    sf::Vector2f widthHeightCalculated = {tempGlyph.textureRect.width*percTexture,tempGlyph.textureRect.height*percTexture};
    std::cout << "textureheight: "<< font->getFont(60).texture.getSize().y<<std::endl;
    std::cout << topLeftCalculated.x << "/"<< topLeftCalculated.y <<std::endl;
    std::cout << widthHeightCalculated.x << "/"<< widthHeightCalculated.y <<std::endl;
    std::cout << tempGlyph.textureRect.width << "/"<< tempGlyph.textureRect.height <<std::endl;

     std::vector<float> temp = {
              // positions          // texture coords
              -0.5f,  0.5f, 0.0f,   topLeftCalculated.x, topLeftCalculated.y,    // top left
              -0.5f, -0.5f, 0.0f,   topLeftCalculated.x, topLeftCalculated.y+widthHeightCalculated.y,   // bottom left
              0.5f, -0.5f, 0.0f,   topLeftCalculated.x+widthHeightCalculated.x, topLeftCalculated.y+widthHeightCalculated.y,   // bottom right
              0.5f, -0.5f, 0.0f,   topLeftCalculated.x+widthHeightCalculated.x, topLeftCalculated.y+widthHeightCalculated.y,   // bottom right
              0.5f,  0.5f, 0.0f,   topLeftCalculated.x+widthHeightCalculated.x, topLeftCalculated.y,   // top right
              -0.5f,  0.5f, 0.0f,  topLeftCalculated.x, topLeftCalculated.y   // top left
      };

    //std::vector<float> temp = {
    //        // positions          // texture coords
    //        -0.5f,  0.5f, 0.0f,  0.0f, 0.0f,// top left
    //        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f,// bottom left
    //        0.5f, -0.5f, 0.0f,   1.0f, 1.0f,   // bottom right
    //        0.5f, -0.5f, 0.0f,   1.0f, 1.0f,   // bottom right
    //        0.5f,  0.5f, 0.0f,   1.0f, 0.0f,// top right
    //        -0.5f,  0.5f, 0.0f,  0.0f, 0.0f// top left
    //};
    glBindTexture(GL_TEXTURE_2D, TEXTURE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,font->getFont(textsize).texture.getSize().x,
            font->getFont(textsize).texture.getSize().y,
            0,GL_RGBA, GL_UNSIGNED_BYTE, font->getFont(textsize).texture.getPixelsPtr());

    glGenerateMipmap(GL_TEXTURE_2D);

    for(char letter:text)
    {
        sf::Glyph tempGlyph = font->getGlyph(letter,textsize);
        vertices.emplace_back(baselinex+cursorPosition);//top left x
        vertices.emplace_back(baseliney);
        cursorPosition+=tempGlyph.advance; //every letter jumps the cursor
    }
    vertices.clear();
    vertices.insert(vertices.end(),temp.begin(),temp.end());
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferSubData(GL_ARRAY_BUFFER,0,vertices.size()* sizeof(float),vertices.data());
    glBindVertexArray(0);
}

SimpleText::SimpleText(StateEssentials &es) {
    essentials = &es;
    glGenTextures(1,&TEXTURE);
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    PROGRAMM = essentials->loader.createProgram({{"text_vertex.glsl",ShaderLoader::VERTEX},
                                                 {"text_fragment.glsl",ShaderLoader::FRAGMENT}});

    vertices = {
            // positions          // texture coords
            -0.5f,  0.5f, 0.0f,   1.0f, 0.0f,    // top left
            -0.5f, -0.5f, 0.0f,   1.0f, 1.0f,   // bottom left
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f,   // bottom right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f,   // bottom right
            0.5f,  0.5f, 0.0f,   0.0f, 0.0f,   // top right
            -0.5f,  0.5f, 0.0f,   1.0f, 0.0f    // top left
    };

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,vertices.size()* sizeof(float),vertices.data(),GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5* sizeof(float),(void*)0); //position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5* sizeof(float),(void*)(3 * sizeof(float))); //textureCoordinates
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
}

void SimpleText::render() {
    essentials->loader.useProgramm(PROGRAMM);
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
