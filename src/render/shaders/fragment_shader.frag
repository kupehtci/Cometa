#version 330 core
out vec4 FragColor;

in vec3 attrColor;

void main()
{
    FragColor = vec4(attrColor, 1.0);
}