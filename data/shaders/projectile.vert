#version 330
layout (location = 0) in vec4 aPos;
layout (location = 1) in vec3 aCol;


out vec4 sizePosition;
out vec3 direction;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    sizePosition = aPos;
    direction  =aCol;
}
