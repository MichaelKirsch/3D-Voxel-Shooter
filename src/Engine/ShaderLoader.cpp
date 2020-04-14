



#include "ShaderLoader.h"

unsigned int ShaderLoader::loadAndCompileShader(std::string obj) {
    unsigned int shaderID;
    std::string last_4_digits = obj.substr(obj.find('.')+1,4);
    bool valid_name = false;

    if(last_4_digits == "vert")
    {
        shaderID = glCreateShader(GL_VERTEX_SHADER);
        valid_name = true;
    }
    if(last_4_digits == "frag" && !valid_name)
    {
        shaderID = glCreateShader(GL_FRAGMENT_SHADER);
        valid_name = true;
    }
    if(last_4_digits == "geom" && !valid_name)
    {
        shaderID = glCreateShader(GL_GEOMETRY_SHADER);
        valid_name = true;
    }
    if(!valid_name)
        throw std::runtime_error("Shader "+ obj + " not valid");

    std::string path_to_shader_dir = std::experimental::filesystem::current_path().parent_path().string();
    path_to_shader_dir +="/data/shaders/";
    std::string path_to_shader = path_to_shader_dir+obj;
    std::ifstream input (path_to_shader);
    std::string shadercode((std::istreambuf_iterator<char>(input)),
                           std::istreambuf_iterator<char>());

    if(shadercode.size()<1)
        throw std::runtime_error("Shadername " + obj+ " does not lead to a file!");
    const GLchar * ch_buf = shadercode.c_str(); //convert the string to a char array

    glShaderSource(shaderID, 1, &ch_buf, NULL);
    glCompileShader(shaderID);
    char infoLog[512];
    int success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
        throw std::runtime_error("Shader "+ obj + " Failed to load\n\n"+std::string(infoLog) + "\n\nLoaded Code:\n" + shadercode);
    }
    return shaderID;
}

unsigned int ShaderLoader::createProgram(std::vector<std::string> shaders_to_attach) {
    std::vector<unsigned int> shaderIDs;
    for(auto sh:shaders_to_attach)
    {
        shaderIDs.emplace_back(loadAndCompileShader(sh));
    }
    return createProgram(shaderIDs);
}

unsigned int ShaderLoader::createProgram(std::vector<unsigned int> shaders) {
    unsigned int progID = glCreateProgram();
    for(auto shader:shaders)
    {
        glAttachShader(progID,shader);
    }
    glBindAttribLocation(progID,2, "aPos");

    glLinkProgram(progID);
    //once we have linked we dont need the shaders anymore so lets delete them
    for(auto shader:shaders)
    {
        glDeleteShader(shader);
    }
    return progID;
}

int ShaderLoader::setUniform(unsigned int& progID, glm::fvec4 input,const std::string &name) {
    int vertexColorLocation = glGetUniformLocation(progID, name.c_str());
    glUniform4f(vertexColorLocation,input.x,input.y,input.z,input.w);
    return vertexColorLocation;
}

int ShaderLoader::setUniform(unsigned int& progID,int input,const std::string &name) {
    int vertexColorLocation = glGetUniformLocation(progID, name.c_str());
    glUniform1i(vertexColorLocation,input);
    return vertexColorLocation;
}

int ShaderLoader::setUniform(unsigned int& progID,float input,const std::string &name) {
    int vertexColorLocation = glGetUniformLocation(progID, name.c_str());
    glUniform1f(vertexColorLocation,input);
    return vertexColorLocation;
}

int ShaderLoader::setUniform(unsigned int& progID,double input,const std::string &name) {
    int vertexColorLocation = glGetUniformLocation(progID, name.c_str());
    glUniform1d(vertexColorLocation,input);
    return vertexColorLocation;
}

int ShaderLoader::setUniform(unsigned int& progID,unsigned int input,const std::string &name) {
    int vertexColorLocation = glGetUniformLocation(progID, name.c_str());
    glUniform1ui(vertexColorLocation,input);
    return vertexColorLocation;
}

int ShaderLoader::setUniform(unsigned int& progID,glm::ivec3 input,const std::string &name) {
    int vertexColorLocation = glGetUniformLocation(progID, name.c_str());
    glUniform3i(vertexColorLocation,input.x,input.y,input.z);
    return vertexColorLocation;
}

int ShaderLoader::setUniform(unsigned int& progID,glm::fvec3 input,const std::string &name) {
    int vertexColorLocation = glGetUniformLocation(progID, name.c_str());
    glUniform3f(vertexColorLocation,input.x,input.y,input.z);
    return vertexColorLocation;
}

int ShaderLoader::setUniform(unsigned int& progID,glm::ivec4 input,const std::string &name) {
    int vertexColorLocation = glGetUniformLocation(progID, name.c_str());
    glUniform4i(vertexColorLocation,input.x,input.y,input.z,input.w);
    return vertexColorLocation;
}


int ShaderLoader::setUniform(unsigned int& progID,std::vector<glm::vec4> input, const std::string &name) {
    int counter =0;
    for(auto el:input)
    {
        setUniform(progID,input[counter],(name+"["+std::to_string(counter)+"]"));
        counter++;
    }
}

void ShaderLoader::useProgramm(unsigned int id) {
    glUseProgram(id);
}

int ShaderLoader::setUniform(unsigned int& progID,glm::mat4 input, const std::string &name) {
    int vertexColorLocation = glGetUniformLocation(progID, name.c_str());
    glUniformMatrix4fv(vertexColorLocation, 1, GL_FALSE, glm::value_ptr(input));
}
