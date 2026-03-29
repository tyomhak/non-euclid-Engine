#version 450 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec3 vWorldPos;
out vec3 vNormal;
out vec2 vTexCoord;

void main()
{
    vec4 worldPos = u_Model * vec4(aPosition, 1.0);
    vWorldPos = worldPos.xyz;
    vNormal   = mat3(transpose(inverse(u_Model))) * aNormal;
    vTexCoord = aTexCoord;

    gl_Position = u_Projection * u_View * worldPos;
}
