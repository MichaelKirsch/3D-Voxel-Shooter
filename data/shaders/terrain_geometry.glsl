#version 330
layout (lines) in;
layout (triangle_strip, max_vertices = 24) out;

out vec3 finalColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


const float size = 0.5;
const vec3 lightDirection = normalize(vec3(0.4,-1.0,0.8));

void createVertex(vec3 offset, vec3 faceNormal)
{
    vec4 actualoffset = vec4(offset * size,0.0);
    vec4 worldposition = gl_in[0].gl_Position + actualoffset;
    vec4 pos = (projection*view) * worldposition;
    gl_Position = pos;
    float brightness = max(dot(-lightDirection,faceNormal),0.3);
    vec3 color = vec3(gl_in[1].gl_Position);
    finalColor = color * brightness;
    EmitVertex();
}

void main() {
    vec3 faceNormal = vec3(0.0, 0.0, 1.0);
    createVertex(vec3(-1.0, 1.0, 1.0), faceNormal);
    createVertex(vec3(-1.0, -1.0, 1.0), faceNormal);
    createVertex(vec3(1.0, 1.0, 1.0), faceNormal);
    createVertex(vec3(1.0, -1.0, 1.0), faceNormal);

    EndPrimitive();

    faceNormal = vec3(1.0, 0.0, 0.0);
    createVertex(vec3(1.0, 1.0, 1.0), faceNormal);
    createVertex(vec3(1.0, -1.0, 1.0), faceNormal);
    createVertex(vec3(1.0, 1.0, -1.0), faceNormal);
    createVertex(vec3(1.0, -1.0, -1.0), faceNormal);

    EndPrimitive();

    faceNormal = vec3(0.0, 0.0, -1.0);
    createVertex(vec3(1.0, 1.0, -1.0), faceNormal);
    createVertex(vec3(1.0, -1.0, -1.0), faceNormal);
    createVertex(vec3(-1.0, 1.0, -1.0), faceNormal);
    createVertex(vec3(-1.0, -1.0, -1.0), faceNormal);

    EndPrimitive();

    faceNormal = vec3(-1.0, 0.0, 0.0);
    createVertex(vec3(-1.0, 1.0, -1.0), faceNormal);
    createVertex(vec3(-1.0, -1.0, -1.0), faceNormal);
    createVertex(vec3(-1.0, 1.0, 1.0), faceNormal);
    createVertex(vec3(-1.0, -1.0, 1.0), faceNormal);

    EndPrimitive();

    faceNormal = vec3(0.0, 1.0, 0.0);
    createVertex(vec3(1.0, 1.0, 1.0), faceNormal);
    createVertex(vec3(1.0, 1.0, -1.0), faceNormal);
    createVertex(vec3(-1.0, 1.0, 1.0), faceNormal);
    createVertex(vec3(-1.0, 1.0, -1.0), faceNormal);

    EndPrimitive();

    faceNormal = vec3(0.0, -1.0, 0.0);
    createVertex(vec3(-1.0, -1.0, 1.0), faceNormal);
    createVertex(vec3(-1.0, -1.0, -1.0), faceNormal);
    createVertex(vec3(1.0, -1.0, 1.0), faceNormal);
    createVertex(vec3(1.0, -1.0, -1.0), faceNormal);

    EndPrimitive();
}
