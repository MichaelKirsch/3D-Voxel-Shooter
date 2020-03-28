#version 330
layout (location = 8) in vec3 aPos;

in vec3 finalColor;

out vec3 finCol;

out vec4 v4pos;
out vec3 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    position = aPos;
    finCol = finalColor;
    gl_Position = vec4(aPos, 1.0);
}
