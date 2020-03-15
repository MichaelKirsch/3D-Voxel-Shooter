

#pragma once

#include <string>
#include <vector>
#include "glad/glad.h"
#include "glm.hpp"
#include <gtc/type_ptr.inl>
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
    void useProgramm(unsigned int id);
    int setUniform(int& input,const std::string &name);
    int setUniform(float& input,const std::string &name);
    int setUniform(double& input,const std::string &name);
    int setUniform(unsigned int& input,const std::string &name);
    int setUniform(glm::ivec3& input , const std::string &name);
    int setUniform(glm::fvec3& input, const std::string &name);
    int setUniform(glm::ivec4& input, const std::string &name);
    int setUniform(glm::fvec4& input, const std::string &name);
    int setUniform(std::vector<glm::vec4>& input, const std::string &name);
    int setUniform(glm::mat4 input, const std::string &name);

    unsigned int current_prog;
    ~ShaderLoader() = default;
private:

    std::string path_to_shader_dir;
    std::map<std::string,unsigned int> programEnum;
protected:
};



