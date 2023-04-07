#version 460

out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;

uniform sampler2D texture_diffuse0;

void main() {
    vec3 color = texture(texture_diffuse0, fs_in.TexCoords).rgb;
    FragColor = vec4(color, 1.0);
}