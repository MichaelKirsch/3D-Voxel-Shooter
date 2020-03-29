#version 330 core
layout (points) in;
layout (points, max_vertices = 1) out;

uniform mat4 view;
uniform mat4 projection;
uniform float chunkSize;
uniform vec3 chunkPosition;

in int i_pos[];

void main() {
    vec3 v;
    v.x =mod(i_pos[0],chunkSize)*2.0;
    v.y =mod((i_pos[0] / chunkSize),chunkSize)*2.0;
    v.z =i_pos[0] / (chunkSize * chunkSize)*2.0;

    int y = int(v.y);
    gl_Position = projection*view*(vec4(v, 1.0) + vec4(chunkPosition.x*chunkSize*2.0,chunkPosition.y*chunkSize*2.0,chunkPosition.z*chunkSize*2.0,1.0));
    EmitVertex();
    EndPrimitive();
}