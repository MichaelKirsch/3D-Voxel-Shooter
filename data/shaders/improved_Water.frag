#version 330 core
in vec3 normals;

out vec4 FragColor;
const vec3 lightDirection = normalize(vec3(0.4,-1.0,0.8));
in vec3 position;
uniform vec3 cameraPos;
uniform vec3 waterColor;

void main() {
    float specularStrength = 0.5;
    vec3 viewDir = normalize(cameraPos - position);
    vec3 reflectDir = reflect(-lightDirection, normalize(normals));
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    float specular = specularStrength * spec ;

    float brightness = max(dot(-lightDirection,normalize(normals)),0.3);
    FragColor = vec4(waterColor*(brightness+specular),0.7);
}
