

#pragma once

#include <string>
#include <vector>
#include "glad/glad.h"
#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <exception>
#include <map>


class ShaderLoader {
public:
    enum SHADERTYPE{
        VERTEX,GEOMETRY,FRAGMENT
    };

    struct ShaderObject
    {
        std::string name;
        SHADERTYPE type;
    };
    ShaderLoader();
    ShaderLoader(std::string path_to_shaderfolder);
    unsigned int loadAndCompileShader(ShaderObject obj);
    unsigned int createProgram(std::vector<ShaderObject> shaders_to_attach);
    unsigned int createProgram(std::vector<unsigned int> shaders);
    void useProgramm(unsigned int id){glUseProgram(id);};
    //void createEnumProgram(std::string prog_name,std::vector<ShaderObject> shaders);
    //void deleteEnumProgram(std::string name);
    //void useEnumProgram(std::string name);
    ~ShaderLoader() = default;
private:
    std::string path_to_shader_dir;
    std::map<std::string,unsigned int> programEnum;
protected:
};



