#version 330
out vec4 FragColor;

in vec3 colorToSet;

void main()
{
    FragColor = vec4(colorToSet,1.0);
}