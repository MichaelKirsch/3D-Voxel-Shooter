

#include "Food.h"

void Food::render() {
    stateEssentials.loader.useProgramm(PROGRAMM);
    glBindVertexArray(VAO);
    stateEssentials.loader.setUniform(stateEssentials.camera.GetViewMatrix(),"view");
    stateEssentials.loader.setUniform(stateEssentials.windowManager.perspectiveProjection,"projection");
    stateEssentials.loader.setUniform(model,"model");
    glDrawArrays(GL_LINES, 0, berries.size());
    glBindVertexArray(0);
}

void Food::update(float &elapsed) {
    model = glm::rotate(model,0.06f,glm::vec3(0.f,1.f,0.f));
}

void Food::create(Terrain &ter, int amount, float respawntime) {
    int found_places = amount;
    int max_tries = 10*amount;
    auto terrain = ter.getTerrainData();
    while(found_places>0 && max_tries>0)
    {
        int x = rand()%ter.getSize();
        int z = rand()%ter.getSize();
        if(ter.isTerrain(x,z))
        {
            int y = ter.getY(x,z);
            BLOCK_TYPE buf = ter.getBlocktype({x,y,z});
            y++;
            Berry buffer;
            buffer.position=glm::vec3(x,y,z);
            //std::cout << x <<"|" << y << "|" << z <<std::endl;
            if(buf==BLOCK_TYPE::SAND)
                buffer.color={0.321, 0.588, 1};
            else if(buf==BLOCK_TYPE::GRASS)
                buffer.color={1, 0.396, 0.2};
            else
                buffer.color={1, 0.721, 0.321};
            bool alreadyplaced = false;
            for(auto& ber:berries)
            {
                if(ber.position.x==x && ber.position.z == z)
                {
                    alreadyplaced=true;
                }
            }
            if(!alreadyplaced)
            {
                berries.emplace_back(buffer);
                found_places--;
            }
        }
        max_tries--;
    }

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,berries.size() * sizeof(Berry),berries.data(),GL_STATIC_DRAW);
    glEnableVertexAttribArray(8);
    glVertexAttribPointer(8, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
}

Food::Food(StateEssentials &es) :stateEssentials(es){
    PROGRAMM=stateEssentials.loader.createProgram({{"berry_fr.glsl",ShaderLoader::FRAGMENT},
                                      {"berry_ge.glsl",ShaderLoader::GEOMETRY},
                                      {"berry_ve.glsl",ShaderLoader::VERTEX}});
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    model = glm::mat4(1.f);
}


