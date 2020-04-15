#version 330
const float M_PI =  3.14159;
layout (location = 0) in vec3 vertex1;
layout (location = 1) in vec3 vertex2;
layout (location = 2) in vec3 vertex3;
const uint mask16bit = 65535;
//data == positionxz,positiony, whichside
out vec3 normals;
const float size = 0.5;
out vec3 position;
uniform mat4 view;
uniform mat4 projection;
uniform float timevalue;
uniform float waterlevel;
uniform float waveheight;
vec3 unpackvertex(vec3 data)
{
    float timev = 5000.f+timevalue;
    vec3 to_return;
    uint positionxz= floatBitsToUint(data.x);
    uint posx = positionxz>>(16) & mask16bit;
    uint posz = positionxz>>(0) & mask16bit;
    to_return.y = cos((data.y*2.0*M_PI)+timev)*waveheight + waterlevel;
    uint whichside_and_unused = floatBitsToUint(data.z);
    uint whichside = (whichside_and_unused>>24);
    if(whichside==0) //nw
    {
        to_return.x = float(posx-size);
        to_return.z = float(posz-size);
    }
    if(whichside==1) //ne
    {
        to_return.x = float(posx+size);
        to_return.z = float(posz-size);
    }
    if(whichside==2) //sw
    {
        to_return.x = float(posx-size);
        to_return.z = float(posz+size);
    }
    if(whichside==3) //se
    {
        to_return.x = float(posx+size);
        to_return.z = float(posz+size);
    }
    return to_return;
}


void main() {
    vec3 vert1 = unpackvertex(vertex1);
    vec3 vert2 = unpackvertex(vertex2);
    vec3 vert3 = unpackvertex(vertex3);

    vec3 ab = vert2-vert1;
    vec3 ac = vert3-vert1;
    normals = normalize(cross(ab,ac));
    vec4 pos = projection*view*vec4(vert1, 1.0);
    gl_Position = pos;
    position = pos.xyz;
}
