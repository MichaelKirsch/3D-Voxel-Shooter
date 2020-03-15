#version 330
out vec4 FragColor;
in float height;
in vec3 normalRaw;
in vec4 pos;

uniform vec3 viewPos;

const vec3 sunPosition = vec3(1000.f,2000.f,1000.f);
const vec3 waterColour = vec3(0.2, 0.4, 0.45);
//vec3 waterColour = vec3(1, 1,1);
const vec3 lightColour = vec3(1.0, 0.6, 0.6);
const float reflectivity = 0.5;
const float shineDamper = 14.0;
const float ambientLighting = 0.3;



void main() {
    vec3 lightDirection =  normalize(vec3(0.4, -1.0, 0.8));
    vec3 normal = normalRaw;
    vec3 viewVector = normalize(viewPos - pos.xyz);
    vec3 reflectedLightDirection = reflect(lightDirection,normal);
    float specularFactor = dot(reflectedLightDirection, viewVector);
    specularFactor = max(pow(specularFactor, shineDamper), 0.0);
    vec3 specularFinal =  lightColour * specularFactor * reflectivity;

    float brightness = max(dot(-lightDirection, normal), ambientLighting);

    vec3 result = ((waterColour*brightness)+specularFinal);
    FragColor = vec4(result, 1.0f);
}
