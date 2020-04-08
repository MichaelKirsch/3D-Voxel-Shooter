#version 330

out vec4 FragColor;

uniform vec3 armorColor;

void main() {
    FragColor = vec4(armorColor,1.0);
}
