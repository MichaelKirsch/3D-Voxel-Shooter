#version 330 core
in vec3 normals;

out vec4 FragColor;

in vec3 position;
uniform vec3 cameraPos;
uniform vec3 waterColor;
uniform vec3 sunpos;
uniform vec4 suncolor;

void main() {


    vec3 lightDirection = normalize(position-sunpos);

    float lightStrength = 1.0- ((1.0/1000.0) * length(position-sunpos));


    float specularStrength = 0.5;
    vec3 viewDir = normalize(cameraPos - position);
    vec3 reflectDir = reflect(-lightDirection, normalize(normals));
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    float specular = specularStrength * spec ;

    float brightness = max(dot(-lightDirection,normalize(normals)),0.3)*lightStrength;
    FragColor = vec4(waterColor*(brightness+specular),0.7);
}
