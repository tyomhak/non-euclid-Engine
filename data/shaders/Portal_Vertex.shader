#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec4 TexCoords;

uniform mat4 mvp;

void main()
{
    TexCoords = mvp * vec4(aPos, 1.0);   
    gl_Position = TexCoords; //projection * view * model * vec4(aPos, 1.0); 
}