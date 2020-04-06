

#include "Ammo.h"

void Ammo::render() {
    StateEssentials::get().loader.useProgramm(PROGRAMM);
    glDisable(GL_BLEND);
    glBindVertexArray(VAO);
    StateEssentials::get().loader.setUniform(StateEssentials::get().camera.GetViewMatrix(),"view");
    StateEssentials::get().loader.setUniform(StateEssentials::get().camera.Position,"cameraPos");
    StateEssentials::get().loader.setUniform(StateEssentials::get().windowManager.perspectiveProjection,"projection");
    StateEssentials::get().loader.setUniform(model,"model");
    glDrawArrays(GL_POINTS, 0, Graphicsbuffer.size()/2);
    glBindVertexArray(0);
    glEnable(GL_BLEND);
}

void Ammo::update(float &elapsed) {
    model = glm::rotate(model,0.06f,glm::vec3(0.f,1.f,0.f));
    bool buffer_cleared =false;
    for(auto& pkg:packages)
    {

        pkg.update(elapsed,need_refactor);
        if(!buffer_cleared&&need_refactor)
        {
            Graphicsbuffer.clear();
            buffer_cleared= true;
        }
        if(need_refactor&&pkg.respawnTimer<0.01
        )
        {
            Graphicsbuffer.emplace_back(pkg.position);
            Graphicsbuffer.emplace_back(pkg.color);
        }
    }
    if(need_refactor)
    {
        glBindBuffer(GL_ARRAY_BUFFER,VBO);
        glBufferSubData(GL_ARRAY_BUFFER,0, Graphicsbuffer.size()* sizeof(glm::vec3) , Graphicsbuffer.data());
        need_refactor = false;
    }
}

void Ammo::create(Terrain &ter, int amount, float respawntime) {
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
            AmmoPackage buffer;
            buffer.position=glm::vec3(x,y,z);
            if(buf==BLOCK_TYPE::SAND)
            {
                buffer.color={0.321, 0.588, 1};
                buffer.m_type = AmmoType::light;
            }

            else if(buf==BLOCK_TYPE::GRASS)
            {
                buffer.color={1, 0.396, 0.2};
                buffer.m_type = AmmoType::heavy;
            }

            else
            {
                buffer.m_type = AmmoType::sniper;
                buffer.color={1, 0.721, 0.321};
            }

            bool alreadyplaced = false;
            for(auto& ber:packages)
            {
                if(ber.position.x==x && ber.position.z == z)
                {
                    alreadyplaced=true;
                }
            }
            if(!alreadyplaced)
            {
                packages.emplace_back(buffer);
                found_places--;
            }
        }
        max_tries--;
    }

    for(auto& graphics_data:packages)
    {
        Graphicsbuffer.emplace_back(graphics_data.position);
        Graphicsbuffer.emplace_back(graphics_data.color);
    }


    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,Graphicsbuffer.size() * sizeof(glm::vec3), Graphicsbuffer.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(8);
    glVertexAttribPointer(8, 3, GL_FLOAT, GL_FALSE, 2*sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(7);
    glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, 2*sizeof(glm::vec3), (void*)sizeof(glm::vec3));
}

Ammo::Ammo() {
    PROGRAMM=StateEssentials::get().loader.createProgram({{"berry_fr.glsl",ShaderLoader::FRAGMENT},
                                      {"berry_ge.glsl",ShaderLoader::GEOMETRY},
                                      {"berry_ve.glsl",ShaderLoader::VERTEX}});
    glGenVertexArrays(1,&VAO);
    std::cout << "food vao:" << VAO<< std::endl;
    glGenBuffers(1,&VBO);

    auto path_to_shader_dir = std::experimental::filesystem::current_path().parent_path().string();
    path_to_shader_dir +="/data/";
    pickupsound.loadFromFile(path_to_shader_dir+"sounds/pickup_ammo.wav");

    model = glm::mat4(1.f);
}

void Ammo::playPickup() {
    sound.setBuffer(pickupsound);
    sound.play();
}


