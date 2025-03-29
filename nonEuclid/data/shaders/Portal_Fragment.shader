#version 330 core
out vec4 FragColor;

in vec4 TexCoords;

uniform sampler2D texture_diffuse1;

void main()
{    
    vec2 ndc = (TexCoords.xy / TexCoords.w) / 2.0 + 0.5;
    FragColor = texture(texture_diffuse1, ndc);
}