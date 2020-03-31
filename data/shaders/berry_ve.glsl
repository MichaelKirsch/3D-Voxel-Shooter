#version 330
layout (location = 8) in vec3 aPos;
layout (location = 7) in vec3 aCol;

out vec3 finCol;

out vec4 v4pos;
out vec3 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    v4pos = vec4(aPos,1.0);
    finCol = aCol;
}
