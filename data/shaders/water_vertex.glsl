#version 330 core
#define M_PI 3.1415926535897932384626433832795
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
out float height;
out vec3 pos;
out vec3 normal;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;
void main()
{
    normal = aNormal;
    height = aPos.y;

    float calcy = sin(aPos.y*(2*M_PI))/2.f;
    pos = vec3(aPos.x, calcy, aPos.z);
    gl_Position = projection*view*model * vec4(aPos.x, calcy, aPos.z, 1.0);

}
