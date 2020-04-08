#version 330 core
#define M_PI 3.1415926535897932384626433832795
layout (location = 0) in vec3 positionAraw;
layout (location = 1) in vec3 positionBraw;
layout (location = 2) in vec3 positionCraw;

out vec3 calculatedNormal;
out vec3 worldPos;


vec3 normal;
vec4 position;

uniform float degrees;
uniform mat4 view;
uniform mat4 projection;

uniform float waveheight;
void main()
{
    vec3 positionA = vec3(positionAraw.x,sin((positionAraw.y*2*M_PI)+degrees)*waveheight,positionAraw.z);
    vec3 positionB = vec3(positionBraw.x,sin((+positionBraw.y*2*M_PI)+degrees)*waveheight,positionBraw.z);
    vec3 positionC = vec3(positionCraw.x,sin((+positionCraw.y*2*M_PI)+degrees)*waveheight,positionCraw.z);
    vec3 ab= positionB-positionA;
    vec3 ac= positionC-positionA;
    normal = cross(ab,ac);
    calculatedNormal = normal;
    position = projection*view*vec4(positionA,1.0);
    gl_Position = position;
    worldPos = position.xyz;
}
