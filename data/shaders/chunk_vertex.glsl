#version 330
layout (location = 2) in vec3 aPos;

uniform mat4 view;
uniform mat4 projection;
uniform float chunkSize;
uniform vec3 chunkPosition;

out vec3 colorToSet;

void main()
{
    int i_pos = gl_VertexID;
    colorToSet = aPos;
    vec3 v;
    v.x =mod(i_pos,chunkSize)*2.0;
    v.y =mod((i_pos / chunkSize),chunkSize)*2.0;
    v.z =i_pos / (chunkSize * chunkSize)*2.0;
    gl_Position = projection*view*(vec4(v, 1.0) + vec4(chunkPosition.x*chunkSize*2.0,chunkPosition.y*chunkSize*2.0,chunkPosition.z*chunkSize*2.0,1.0));
}