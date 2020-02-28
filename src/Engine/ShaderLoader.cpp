


#include "ShaderLoader.h"

ShaderLoader::ShaderLoader(std::string path_to_shaderfolder) {
    path_to_shader_dir = path_to_shaderfolder;
}

ShaderLoader::ShaderLoader() {
    path_to_shader_dir = std::experimental::filesystem::current_path().parent_path().string();
    path_to_shader_dir +="/data/shaders/";
}

unsigned int ShaderLoader::loadAndCompileShader(ShaderObject obj) {
    unsigned int shaderID;
    switch(obj.type)
    {
        case SHADERTYPE::VERTEX:
            shaderID = glCreateShader(GL_VERTEX_SHADER);
            break;
        case SHADERTYPE::FRAGMENT:
            shaderID = glCreateShader(GL_FRAGMENT_SHADER);
            break;
        case SHADERTYPE::GEOMETRY:
            shaderID = glCreateShader(GL_GEOMETRY_SHADER);
            break;
    }
    std::string path_to_shader = path_to_shader_dir+obj.name;
    std::ifstream input (path_to_shader);
    std::string shadercode((std::istreambuf_iterator<char>(input)),
                           std::istreambuf_iterator<char>());
    const GLchar * ch_buf = shadercode.c_str(); //convert the string to a char array
    glShaderSource(shaderID, 1, &ch_buf, NULL);
    glCompileShader(shaderID);
    char infoLog[512];
    int success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
        throw std::runtime_error("Shader Failed to load\n\n"+std::string(infoLog));
    }
    return shaderID;
}

unsigned int ShaderLoader::createProgram(std::vector<ShaderObject> shaders_to_attach) {
    std::vector<unsigned int> shaderIDs;
    for(auto sh:shaders_to_attach)
    {
        shaderIDs.emplace_back(loadAndCompileShader(sh));
    }
    return createProgram(shaderIDs);
}

unsigned int ShaderLoader::createProgram(std::vector<unsigned int> shaders) {
    unsigned int current_prog = glCreateProgram();
    for(auto shader:shaders)
    {
        glAttachShader(current_prog,shader);
    }
    glLinkProgram(current_prog);
    //once we have linked we dont need the shaders anymore so lets delete them
    for(auto shader:shaders)
    {
        glDeleteShader(shader);
    }
    return current_prog;
}
