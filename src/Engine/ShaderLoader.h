

#pragma once

#include <string>
#include <vector>
#include "glad/glad.h"
#include "glm.hpp"
#include <gtc/type_ptr.inl>
#include <fstream>
#include <iostream>
#include <exception>
#include <map>


namespace ShaderLoader
{
    unsigned int loadAndCompileShader(std::string name);
    unsigned int createProgram(std::vector<std::string> shaders_to_attach);
    unsigned int createProgram(std::vector<unsigned int> shaders);
    void useProgramm(unsigned int id);
    int setUniform(unsigned int &progID, int input,const std::string &name);
    int setUniform(unsigned int &progID, float input,const std::string &name);
    int setUniform(unsigned int &progID, double input,const std::string &name);
    int setUniform(unsigned int &progID, unsigned int input,const std::string &name);
    int setUniform(unsigned int &progID, glm::ivec3 input , const std::string &name);
    int setUniform(unsigned int &progID, glm::fvec3 input, const std::string &name);
    int setUniform(unsigned int &progID, glm::ivec4 input, const std::string &name);
    int setUniform(unsigned int &progID, glm::fvec4 input, const std::string &name);
    int setUniform(unsigned int &progID, std::vector<glm::vec4> input, const std::string &name);
    int setUniform(unsigned int &progID, glm::mat4 input, const std::string &name);
}




