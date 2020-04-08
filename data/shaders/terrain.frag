#version 330
out vec4 FragColor;
in vec3 finalColor;
in vec3 position;
void main() {
    FragColor = vec4(finalColor,1.0);
}
