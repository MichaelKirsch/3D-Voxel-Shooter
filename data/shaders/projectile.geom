#version 330
layout (points) in;
layout (triangle_strip, max_vertices = 24) out;

out vec3 finalColor;
out vec2 o_texCoord;

in vec4 sizePosition[];
in vec3 direction[];

uniform vec3 cameraPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

float size = 0.25;
const vec3 lightDirection = normalize(vec3(0.4,-1.0,0.8));

void createVertex(vec3 offset, vec3 faceNormal, vec2 texCoord)
{
    vec4 rawdata = sizePosition[0];
    vec4 actualoffset = vec4(offset * rawdata.x,0.0);
    vec4 woldposition = vec4(rawdata.yzw,1.0)+actualoffset;
    vec4 pos = (projection*view) * woldposition;
    gl_Position = pos;
    float brightness = max(dot(-lightDirection,faceNormal),0.3);
    vec3 color = vec3(0.921, 0.545, 0);
    finalColor = color;// * brightness;
    o_texCoord = texCoord;
    EmitVertex();
}

void main() {
    mat3 rot = mat3(1.0);
    vec3 faceNormal = vec3(0.0, 0.0, 1.0)*rot;
    createVertex(vec3(-1.0, 1.0, 1.0), faceNormal,vec2(0.0,1.0));
    createVertex(vec3(-1.0, -1.0, 1.0), faceNormal,vec2(0.0,0.0));
    createVertex(vec3(1.0, 1.0, 1.0), faceNormal,vec2(1.0,1.0));
    createVertex(vec3(1.0, -1.0, 1.0), faceNormal,vec2(1.0,0.0));

    EndPrimitive();

    faceNormal = vec3(1.0, 0.0, 0.0)*rot;
    createVertex(vec3(1.0, 1.0, 1.0), faceNormal,vec2(0.0,1.0));
    createVertex(vec3(1.0, -1.0, 1.0), faceNormal,vec2(0.0,0.0));
    createVertex(vec3(1.0, 1.0, -1.0), faceNormal,vec2(1.0,1.0));
    createVertex(vec3(1.0, -1.0, -1.0), faceNormal,vec2(1.0,0.0));

    EndPrimitive();

    faceNormal = vec3(0.0, 0.0, -1.0)*rot;
    createVertex(vec3(1.0, 1.0, -1.0), faceNormal,vec2(0.0,1.0));
    createVertex(vec3(1.0, -1.0, -1.0), faceNormal,vec2(0.0,0.0));
    createVertex(vec3(-1.0, 1.0, -1.0), faceNormal,vec2(1.0,1.0));
    createVertex(vec3(-1.0, -1.0, -1.0), faceNormal,vec2(1.0,0.0));

    EndPrimitive();

    faceNormal = vec3(-1.0, 0.0, 0.0)*rot;
    createVertex(vec3(-1.0, 1.0, -1.0), faceNormal,vec2(0.0,1.0));
    createVertex(vec3(-1.0, -1.0, -1.0), faceNormal,vec2(0.0,0.0));
    createVertex(vec3(-1.0, 1.0, 1.0), faceNormal,vec2(1.0,1.0));
    createVertex(vec3(-1.0, -1.0, 1.0), faceNormal,vec2(1.0,0.0));

    EndPrimitive();

    faceNormal = vec3(0.0, 1.0, 0.0)*rot;
    createVertex(vec3(1.0, 1.0, 1.0), faceNormal,vec2(0.0,1.0));
    createVertex(vec3(1.0, 1.0, -1.0), faceNormal,vec2(0.0,0.0));
    createVertex(vec3(-1.0, 1.0, 1.0), faceNormal,vec2(1.0,1.0));
    createVertex(vec3(-1.0, 1.0, -1.0), faceNormal,vec2(1.0,0.0));

    EndPrimitive();

    faceNormal = vec3(0.0, -1.0, 0.0)*rot;
    createVertex(vec3(-1.0, -1.0, 1.0), faceNormal,vec2(0.0,1.0));
    createVertex(vec3(-1.0, -1.0, -1.0), faceNormal,vec2(0.0,0.0));
    createVertex(vec3(1.0, -1.0, 1.0), faceNormal,vec2(1.0,1.0));
    createVertex(vec3(1.0, -1.0, -1.0), faceNormal,vec2(1.0,0.0));

    EndPrimitive();
}
