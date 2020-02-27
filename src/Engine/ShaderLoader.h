

#pragma once

#include <string>
#include <vector>
#include "glad/glad.h"

enum class SHADERTYPE{
    VERTEX,GEOMETRY,FRAGMENT
};

struct ShaderObject
{
    std::string name;
    SHADERTYPE;
};


class ShaderLoader {
public:
    ShaderLoader(std::string path_to_shaderfolder);
    unsigned int loadAndCompileShader(ShaderObject obj);
    unsigned int loadAndCompileShader(std::string name, SHADERTYPE type);
    unsigned int createProgram(std::vector<ShaderObject> shaders_to_attach);
    unsigned int createProgram(std::vector<unsigned int> shaders);
    void useProgramm(unsigned int id){glUseProgram(id);};
    ~ShaderLoader() = default;
private:
protected:
};



