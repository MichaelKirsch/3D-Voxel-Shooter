

#include <Engine/StateMachine/Essential.h>
#include "ImprovedWater.h"


void ImprovedWater::create(ImprovedTerrain &r_terrain, float waterlevel) {
    p_terrain = &r_terrain;
    m_noise.SetNoiseType(FastNoise::Simplex);
    m_noise.SetFrequency(0.1f);
    m_waterlevel = r_terrain.getMaxTerrainHeight()*waterlevel;
    for(int x=0;x<r_terrain.getSize();x++)
    {
        for(int z=0;z<r_terrain.getSize();z++)
        {
            if(r_terrain.getHeightOfTerrain(x,z)<m_waterlevel)
            {
                raw_tiles.emplace_back(generateTile(x,z));
            }
        }
    }
    for(auto tile:raw_tiles)
    {
        convertWatertileToFloatAndAddToVBOdata(tile);
    }

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,vbo_data.size()* sizeof(glm::vec3),vbo_data.data(),GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(glm::vec3),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,3 * sizeof(glm::vec3),(void*)(sizeof(glm::vec3)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,3 * sizeof(glm::vec3),(void*)(2*sizeof(glm::vec3)));
    glEnableVertexAttribArray(2);
    std::cout << "tiles: " << vbo_data.size()/3 << std::endl;
}

WaterTile ImprovedWater::generateTile(int x, int z) {
    WaterTile buf;
    buf.x_pos_base =x;
    buf.z_pos_base =z;
    buf.y_pos_leftup = m_noise.GetNoise(static_cast<float>(x-size), static_cast<float>(z-size));
    buf.y_pos_leftbottom = m_noise.GetNoise(static_cast<float>(x-size), static_cast<float>(z+size));
    buf.y_pos_rightup = m_noise.GetNoise(static_cast<float>(x+size), static_cast<float>(z-size));
    buf.y_pos_rightbottom = m_noise.GetNoise(static_cast<float>(x+size), static_cast<float>(z+size));
    return buf;
}

void ImprovedWater::convertWatertileToFloatAndAddToVBOdata(WaterTile tile) {

    WaterVertex vert_nw,vert_ne,vert_sw,vert_se;
    vert_nw.posy_own = m_noise.GetNoise(tile.x_pos_base-size,tile.z_pos_base-size);
    vert_nw.posx = tile.x_pos_base;
    vert_nw.posz = tile.z_pos_base;
    vert_nw.vertex = nw;

    vert_ne.posy_own = m_noise.GetNoise(tile.x_pos_base+size,tile.z_pos_base-size);
    vert_ne.posx = tile.x_pos_base;
    vert_ne.posz = tile.z_pos_base;
    vert_ne.vertex = ne;

    vert_sw.posy_own = m_noise.GetNoise(tile.x_pos_base-size,tile.z_pos_base+size);
    vert_sw.posx = tile.x_pos_base;
    vert_sw.posz = tile.z_pos_base;
    vert_sw.vertex = sw;

    vert_se.posy_own = m_noise.GetNoise(tile.x_pos_base+size,tile.z_pos_base+size);
    vert_se.posx = tile.x_pos_base;
    vert_se.posz = tile.z_pos_base;
    vert_se.vertex = se;

    //triangle one
    std::vector<glm::vec3> triangle1={waterVertexToRaw(vert_nw),waterVertexToRaw(vert_sw),waterVertexToRaw(vert_ne),
                                      waterVertexToRaw(vert_sw),waterVertexToRaw(vert_ne),waterVertexToRaw(vert_nw),
                                      waterVertexToRaw(vert_ne),waterVertexToRaw(vert_nw),waterVertexToRaw(vert_sw)};

    //triangle two
    std::vector<glm::vec3> triangle2={waterVertexToRaw(vert_se),waterVertexToRaw(vert_ne),waterVertexToRaw(vert_sw),
                                      waterVertexToRaw(vert_ne),waterVertexToRaw(vert_sw),waterVertexToRaw(vert_ne),
                                      waterVertexToRaw(vert_sw),waterVertexToRaw(vert_se),waterVertexToRaw(vert_ne)};

    vbo_data.insert(vbo_data.end(),triangle1.begin(),triangle1.end());
    vbo_data.insert(vbo_data.end(),triangle2.begin(),triangle2.end());
}

glm::vec3 ImprovedWater::waterVertexToRaw(WaterVertex vert) {
    glm::vec3 buffer;

    glm::uint32 xz;
    xz = vert.posx;
    xz = (xz << 16) + vert.posz;

    glm::uint32 vertex_and_unused;
    vertex_and_unused = vert.vertex;
    vertex_and_unused = (vertex_and_unused<<8) + vert.unused;
    vertex_and_unused = (vertex_and_unused<<16) + vert.unused2;

    buffer.x = glm::uintBitsToFloat(xz);
    buffer.y = vert.posy_own;
    buffer.z = glm::uintBitsToFloat(vertex_and_unused);

    return buffer;
}

ImprovedWater::ImprovedWater() {
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    PROGRAMM= ShaderLoader::createProgram({{"improved_Water.frag"},{"improved_Water.vert"}});
}

void ImprovedWater::render() {
    glDisable(GL_CULL_FACE);
    ShaderLoader::useProgramm(PROGRAMM);
    ShaderLoader::setUniform(PROGRAMM,StateEssentials::get().windowManager.perspectiveProjection,"projection");
    ShaderLoader::setUniform(PROGRAMM,StateEssentials::get().camera.GetViewMatrix(),"view");
    ShaderLoader::setUniform(PROGRAMM,(float)m_waterlevel,"waterlevel");
    ShaderLoader::setUniform(PROGRAMM,glm::vec3(0.141, 0.752, 1),"waterColor");
    ShaderLoader::setUniform(PROGRAMM,0.1f,"waveheight");
    ShaderLoader::setUniform(PROGRAMM,degrees,"degrees");
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES,0,vbo_data.size()/3);
    glBindVertexArray(0);
    glEnable(GL_CULL_FACE);
}

ImprovedWater::~ImprovedWater() {
    glDeleteBuffers(1,&VBO);
    glDeleteVertexArrays(1,&VAO);
}

void ImprovedWater::update(float &elapsed) {
    degrees+=0.04f;
}



