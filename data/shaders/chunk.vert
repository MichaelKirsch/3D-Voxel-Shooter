#version 430 core
layout (location = 2) in vec2 data;

uniform mat4 view;
uniform mat4 projection;
uniform float chunkSize;
uniform vec3 chunkPosition;

out vec2 o_data;

void main()
{
    o_data = data;
}