#version 330
out vec4 FragColor;
in vec3 position;
void main() {

    FragColor = vec4((1.0/100.0)*position.x,0.0,1.0-((1.0/100.0)*position.z), 1.0);
}
