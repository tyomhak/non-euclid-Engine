#version 450 core

in vec3 vWorldPos;
in vec3 vNormal;
in vec2 vTexCoord;

uniform sampler2D u_Texture;
uniform vec3 u_ViewPos;

out vec4 FragColor;

// Hardcoded directional light (will be made configurable in a later phase).
const vec3 LIGHT_DIR   = normalize(vec3(0.3, -1.0, -0.5));
const vec3 LIGHT_COLOR = vec3(1.0);
const float AMBIENT    = 0.15;
const float SPECULAR_STRENGTH = 0.5;
const float SHININESS  = 32.0;

void main()
{
    vec3 normal = normalize(vNormal);
    vec3 texColor = texture(u_Texture, vTexCoord).rgb;

    // Ambient
    vec3 ambient = AMBIENT * texColor;

    // Diffuse (flip light dir for dot product)
    float diff = max(dot(normal, -LIGHT_DIR), 0.0);
    vec3 diffuse = diff * LIGHT_COLOR * texColor;

    // Specular (Blinn-Phong)
    vec3 viewDir = normalize(u_ViewPos - vWorldPos);
    vec3 halfDir = normalize(viewDir + (-LIGHT_DIR));
    float spec = pow(max(dot(normal, halfDir), 0.0), SHININESS);
    vec3 specular = SPECULAR_STRENGTH * spec * LIGHT_COLOR;

    FragColor = vec4(ambient + diffuse + specular, 1.0);
}
