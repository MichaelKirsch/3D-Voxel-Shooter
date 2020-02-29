#version 330
out vec4 FragColor;
in float height;
in vec3 normal;
in vec3 pos;

uniform vec3 viewPos;

void main() {

    float specularStrength = 0.7;
    vec3 sun_position=vec3(1000.f,1000.f,1000.f);
    vec3 lightColor = vec3(1.f,1.f,0.95f);
    vec3 lightDir = normalize(sun_position - pos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    vec3 objectColor = vec3(0.25f,0.9f,1.0f);

    vec3 viewDir = normalize(viewPos - pos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 4);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = height * objectColor;
    FragColor = vec4(result, 1.0f);
}
