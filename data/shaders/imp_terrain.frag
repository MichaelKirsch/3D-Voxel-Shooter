#version 330 core

out vec4 FragColor;

in vec3 outColor;
in vec3 normalOut;
in vec3 fragPos;

uniform vec3 playerPos;
uniform vec4 fogColor;
uniform float fogdistance;
uniform vec3 sunpos;
uniform vec4 suncolor;
const float perc = 1.0/255;
uniform mat4 view;
uniform mat4 projection;


void main() {

    vec3 lightDirection = normalize(fragPos-sunpos);

    float brightness =  max(dot(normalOut,-lightDirection),0.7);

    float fogFactor =0.f;


    float dist = distance(fragPos.xz,playerPos.xz);
    vec4 nomrmalColor = vec4(outColor/255,1.0)*brightness;

    if(dist>fogdistance)
    {
        FragColor = fogColor;
    }
    else
    {
        if(dist>fogdistance/2)
        {
            float half_distance_perc = 1.0/(fogdistance/2);
            float used_distance = dist-(fogdistance/2);
            fogFactor = used_distance*half_distance_perc;
        }
        if(dist<fogdistance/2)
        {
            FragColor = nomrmalColor;
        }
        FragColor = nomrmalColor*(1.0-fogFactor)+(fogFactor*fogColor);
    }
}
