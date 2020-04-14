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



    if(which_vertex == 0)
    {
        //front left  bottom vertex
        rawPosition+=vec3(-size,-size,size);
    }
    if(which_vertex == 1)
    {
        //front right  bottom vertex
        rawPosition+=vec3(size,-size,size);
    }
    if(which_vertex == 2)
    {
        //front right top vertex
        rawPosition+=vec3(size,size,size);
    }
    if(which_vertex == 3)
    {
        //front left top vertex
        rawPosition+=vec3(-size,size,size);
    }

    if(which_vertex == 4)
    {
        //back left bottom
        rawPosition+=vec3(-size,-size,-size);
    }
    if(which_vertex == 5)
    {
        //back  right bottom
        rawPosition+=vec3(size,-size,-size);
    }

    if(which_vertex == 6)
    {
        //back left top
        rawPosition+=vec3(size,size,-size);
    }
    if(which_vertex == 7)
    {
        //back  right top
        rawPosition+=vec3(-size,size,-size);
    }

    //left=0,right,up,down,front,back,underwater,_spare_bit

    if(normal==0)
    {
        normalOut=vec3(-1.0,0.0,0.0);
    }
    if(normal==1)
    {
        normalOut=vec3(1.0,0.0,0.0);
    }
    if(normal==2)
    {
        normalOut=vec3(0.0,1.0,0.0);
    }
    if(normal==3)
    {
        normalOut=vec3(0.0,-1.0,0.0);
    }
    if(normal==4)
    {
        normalOut=vec3(0.0,0.0,1.0);
    }
    if(normal==5)
    {
        normalOut=vec3(0.0,0.0,-1.0);
    }

    vec4 pos =   projection*view*(vec4(rawPosition,1.0));
    gl_Position = pos;
    fragPos = pos.xyz;

}
