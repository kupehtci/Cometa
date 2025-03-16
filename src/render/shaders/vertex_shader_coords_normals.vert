//#version 330 core
//
//layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aNormal; 
//layout (location = 2) in vec3 aColor;
//layout (location = 3) in vec2 aTexCoord;
//
//// uniform mat4 uProjection; 
//// uniform mat4 uView; 
//uniform mat4 uViewProjection; 
//uniform mat4 uModel; 
//
//out vec3 FragPos; 
//out vec3 ourColor; 
//out vec2 texCoord;
//out vec3 Normal; 
//
//void main()
//{
//    // gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0f);
//    FragPos = vec3(uModel * vec4(aPos, 1.0));
//
//    gl_Position = uViewProjection * uModel * vec4(aPos, 1.0); 
//
//    Normal = mat3(transpose(inverse(uModel))) * aNormal; 
//    
//    ourColor = aColor;
//    texCoord = aTexCoord; 
//}
//
//

#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal; 
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTexCoord;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 uModel;
uniform mat4 uViewProjection;

void main()
{
    FragPos = vec3(uModel * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(uModel))) * aNormal;  
    
    gl_Position = uViewProjection * vec4(FragPos, 1.0);
}