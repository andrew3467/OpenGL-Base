#version 460

out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} vs_out;


vec3 viewPos;

vec3 lightPos;

uniform sampler2D texture_diffuse0;

void main() {
    vec3 result = texture(texture_diffuse0, vs_out.TexCoords).rgb;


    FragColor = vec4(result, 1.0);
}