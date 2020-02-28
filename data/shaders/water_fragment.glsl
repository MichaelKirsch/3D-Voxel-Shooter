#version 330
out vec4 FragColor;
in float height;
void main() {
    FragColor = vec4(height,height,height, 1.0f);
}
