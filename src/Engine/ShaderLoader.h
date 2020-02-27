

#pragma once

#include <string>
class ShaderLoader {
public:
    enum SHADERTYPE{
        VERTEX,GEOMETRY,FRAGMENT
    };
    ShaderLoader(std::string path_to_shaderfolder);

    ~ShaderLoader() = default;

private:
protected:
};



