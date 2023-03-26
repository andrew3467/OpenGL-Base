#version 460 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} vs_out;

uniform sampler2D texture_diffuse1;

void main()
{
    FragColor = texture(texture_diffuse1, vs_out.TexCoords);
}
