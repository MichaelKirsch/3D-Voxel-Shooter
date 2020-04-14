#version 330 core

out vec4 FragColor;

in vec3 outColor;
in vec3 normalOut;
in vec3 fragPos;

const vec3 lightDirection = normalize(vec3(0.4,-1.0,0.8));
uniform vec3 playerPos;
uniform vec4 fogColor;
uniform float fogdistance;
const float perc = 1.0/255;

void main() {

    float brightness = max(dot(-lightDirection,normalOut),0.3);


    float fogFactor =0.f;


    float dist = distance(fragPos.xz,playerPos.xz);
    vec4 nomrmalColor = vec4(outColor,1.0)*perc*brightness;

    if(dist>fogdistance)
        nomrmalColor = fogColor;

    if(dist>fogdistance/2)
    {
        float half_distance_perc = 1.0/(fogdistance/2);
        float used_distance = dist-(fogdistance/2);
        fogFactor = used_distance*half_distance_perc;
    }
    FragColor = nomrmalColor*(1.0-fogFactor)+(fogFactor*fogColor);
}
