#version 330 core

layout (location = 0) in vec3 data;

out vec3 outColor;
out vec3 normalOut;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 cameraPos;
uniform vec3 chunkOffset;
const uint mask8bit = 255;
const uint mask16bit = 65535;
const float size = 0.5f;

void main() {



    uint position_x_y = floatBitsToUint(data.y);
    uint position_z_which_spare = floatBitsToUint(data.z);
    uint colors = floatBitsToUint(data.x);

    uint color_red = colors>>(24) & mask8bit;
    uint color_green = colors>>(16) & mask8bit;
    uint color_blue = colors>>(8) & mask8bit;
    uint normal = colors>>(0) & mask8bit;

    uint posx = position_x_y>>(16) & mask16bit;
    uint posy = position_x_y>>(0) & mask16bit;
    uint posz = position_z_which_spare>>(16) & mask16bit;
    uint which_vertex = position_z_which_spare>>(8) & mask8bit;
    uint spare = position_z_which_spare>>(0) & mask8bit;

    outColor = vec3(color_red,color_green,color_red);

    vec3 rawPosition = vec3(posx,posy,posz);

    switch(which_vertex)
    {
        case 0:
        rawPosition+=vec3(-size,-size,size);
        break;
        case 1:
        rawPosition+=vec3(size,-size,size);
        break;
        case 2:
        rawPosition+=vec3(size,size,size);
        break;
        case 3:
        rawPosition+=vec3(-size,size,size);
        break;
        case 4:
        rawPosition+=vec3(-size,-size,-size);
        break;
        case 5:
        rawPosition+=vec3(size,-size,-size);
        break;
        case 6:
        rawPosition+=vec3(size,size,-size);
        break;
        case 7:
        rawPosition+=vec3(-size,size,-size);
        break;
    }

    switch (normal)
    {
        case 0:
        normalOut=vec3(-1.0,0.0,0.0);
        break;
        case 1:
        normalOut=vec3(1.0,0.0,0.0);
        break;
        case 2:
        normalOut=vec3(0.0,1.0,0.0);
        break;
        case 3:
        normalOut=vec3(0.0,-1.0,0.0);
        break;
        case 4:
        normalOut=vec3(0.0,0.0,1.0);
        break;
        case 5:
        normalOut=vec3(0.0,0.0,-1.0);
        break;
    }

    //left=0,right,up,down,front,back,underwater,_spare_bit

    vec4 pos =   projection*view*(vec4(rawPosition,1.0));
    gl_Position = pos;
    fragPos = pos.xyz;

}
