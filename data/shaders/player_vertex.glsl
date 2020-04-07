#version 330
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 worldPos;


void main() {
    vec4 translatedPos = vec4(aPos,1.0)*model;
    translatedPos = translatedPos+worldPos;
    gl_Position = projection*view*translatedPos;
}
