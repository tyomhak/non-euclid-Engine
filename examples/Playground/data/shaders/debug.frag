#version 450 core

out vec4 FragColor;

// Flat debug color — useful for wireframe, collision shapes, etc.
const vec3 DEBUG_COLOR = vec3(0.0, 1.0, 0.0);

void main()
{
    FragColor = vec4(DEBUG_COLOR, 1.0);
}
