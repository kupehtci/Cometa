#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal; 
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTexCoord;

// out vec3 attrColor;
out vec3 ourColor; 
out vec2 texCoord;

uniform mat4 uViewProjection; 
uniform mat4 uModel; 

void main()
{
    gl_Position = uViewProjection * uModel * vec4(aPos, 1.0); 
    ourColor = aColor;
}