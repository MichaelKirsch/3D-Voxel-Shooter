#version 330
layout (points) in;
layout (triangle_strip, max_vertices = 24) out;

out vec3 finalColor;

in vec4 v4pos[];
in vec3 finCol[];

uniform mat4 model;
uniform vec3 cameraPos;
uniform mat4 view;
uniform mat4 projection;

float size = 0.25;
const vec3 lightDirection = normalize(vec3(0.4,-1.0,0.8));

void createVertex(vec3 offset, vec3 faceNormal)
{
    vec4 actualoffset = vec4(offset * size,0.0);
    actualoffset*=model;
    vec4 worldposition = v4pos[0] + actualoffset;
    vec4 pos = (projection*view) * worldposition;
    gl_Position = pos;
    float brightness = max(dot(-lightDirection,faceNormal),0.3);
    vec3 color = finCol[0];
    finalColor = color * brightness;
    EmitVertex();
}

void main() {
    if(distance(cameraPos,v4pos[0].xyz)<10.f)
    {
        size = 0.125f;
    }
    mat3 rot = mat3(model);
    vec3 faceNormal = vec3(0.0, 0.0, 1.0)*rot;
    createVertex(vec3(-1.0, 1.0, 1.0), faceNormal);
    createVertex(vec3(-1.0, -1.0, 1.0), faceNormal);
    createVertex(vec3(1.0, 1.0, 1.0), faceNormal);
    createVertex(vec3(1.0, -1.0, 1.0), faceNormal);

    EndPrimitive();

    faceNormal = vec3(1.0, 0.0, 0.0)*rot;
    createVertex(vec3(1.0, 1.0, 1.0), faceNormal);
    createVertex(vec3(1.0, -1.0, 1.0), faceNormal);
    createVertex(vec3(1.0, 1.0, -1.0), faceNormal);
    createVertex(vec3(1.0, -1.0, -1.0), faceNormal);

    EndPrimitive();

    faceNormal = vec3(0.0, 0.0, -1.0)*rot;
    createVertex(vec3(1.0, 1.0, -1.0), faceNormal);
    createVertex(vec3(1.0, -1.0, -1.0), faceNormal);
    createVertex(vec3(-1.0, 1.0, -1.0), faceNormal);
    createVertex(vec3(-1.0, -1.0, -1.0), faceNormal);

    EndPrimitive();

    faceNormal = vec3(-1.0, 0.0, 0.0)*rot;
    createVertex(vec3(-1.0, 1.0, -1.0), faceNormal);
    createVertex(vec3(-1.0, -1.0, -1.0), faceNormal);
    createVertex(vec3(-1.0, 1.0, 1.0), faceNormal);
    createVertex(vec3(-1.0, -1.0, 1.0), faceNormal);

    EndPrimitive();

    faceNormal = vec3(0.0, 1.0, 0.0)*rot;
    createVertex(vec3(1.0, 1.0, 1.0), faceNormal);
    createVertex(vec3(1.0, 1.0, -1.0), faceNormal);
    createVertex(vec3(-1.0, 1.0, 1.0), faceNormal);
    createVertex(vec3(-1.0, 1.0, -1.0), faceNormal);

    EndPrimitive();

    faceNormal = vec3(0.0, -1.0, 0.0)*rot;
    createVertex(vec3(-1.0, -1.0, 1.0), faceNormal);
    createVertex(vec3(-1.0, -1.0, -1.0), faceNormal);
    createVertex(vec3(1.0, -1.0, 1.0), faceNormal);
    createVertex(vec3(1.0, -1.0, -1.0), faceNormal);

    EndPrimitive();
}
