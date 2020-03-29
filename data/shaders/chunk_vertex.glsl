#version 330
layout (location = 2) in vec2 aPos;

uniform mat4 view;
uniform mat4 projection;
uniform float chunkSize;
uniform vec3 chunkPosition;

out vec3 colorToSet;
out int i_pos;

void main()
{
    i_pos = gl_VertexID;
    colorToSet = vec3(0.0,0.1,0.0);
}