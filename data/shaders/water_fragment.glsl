#version 330
out vec4 FragColor;

const vec3 lightDirection = normalize(vec3(0.4,-1.0,0.8));
in vec3 calculatedNormal;
in vec3 worldPos;

uniform vec3 WaterColor;

void main() {
    float brightness = max(dot(-lightDirection,calculatedNormal),0.3);
    FragColor = vec4(WaterColor,1.0)*brightness;
}
