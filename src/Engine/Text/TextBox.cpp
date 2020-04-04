

#include "TextBox.h"

void TextBox::render() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    stateEssentials->loader.useProgramm(PROGRAM);
    glBindTexture(GL_TEXTURE_2D,texturePtr);
    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}

void TextBox::update(float &elapsed) {
}

void TextBox::create(StateEssentials &es, std::string fontname) {
    stateEssentials = &es;
    path_to_fonts = std::experimental::filesystem::current_path().parent_path().string();

    PROGRAM = stateEssentials->loader.createProgram({{"text_vertex.glsl",ShaderLoader::VERTEX},
                                                     {"text_fragment.glsl",ShaderLoader::FRAGMENT}});

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&IBO);
    glGenTextures(1,&texturePtr);
    if(!m_font.loadFromFile(path_to_fonts+"/data/fonts/"+fontname))
    {
        throw std::runtime_error("fonts cant be loaded");
    }
    for(auto& character:m_charSet)
    {
        m_font.getGlyph(character,textsize, false);
    }

    const sf::Texture& temp = m_font.getTexture(textsize);
    m_Texture = temp.copyToImage();

    //if(!m_Texture.loadFromFile(path_to_fonts+"/data/textures/" + "aix.png"))
        //throw std::runtime_error("Cant opengl file");

    glBindTexture(GL_TEXTURE_2D, texturePtr);
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA ,m_Texture.getSize().x, m_Texture.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Texture.getPixelsPtr());
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    float vertices[] = {
            // positions          // colors           // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,   // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,   // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,   // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f    // top left
    };

    unsigned int indices[] = {  // note that we start from 0!
            3,1,0,   // first triangle
           3,2,1    // second triangle
    };


    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),&vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6* sizeof(float)));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);
}

