#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform

void main()
{
    gl_position = uProyection * uView * uModel * vec4(aPos, 1.0f);
}