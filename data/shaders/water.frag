#version 330
out vec4 FragColor;

const vec3 lightDirection = normalize(vec3(0.4,-1.0,0.8));
in vec3 calculatedNormal;
in vec3 worldPos;

const vec3 lightColor=vec3(1, 0.945, 0.721);

uniform vec3 cameraPos;
uniform vec3 WaterColor;

void main() {


    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(cameraPos - worldPos);
    vec3 reflectDir = reflect(-lightDirection, calculatedNormal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    float specular = specularStrength * spec ;


    float brightness = max(dot(-lightDirection,calculatedNormal),0.3);
    FragColor = vec4(WaterColor,1.0)*(brightness+specular);
}
