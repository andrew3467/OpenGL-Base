#version 460

#define MAX_POINT_LIGHTS 32
#define MAX_SPOT_LIGHTS 8
#define MAX_DIR_LIGHTS 4

out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} vs_in;

struct PointLight{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};


vec3 viewPos;

int numPointLights;
PointLight pointLights[MAX_POINT_LIGHTS];

uniform sampler2D texture_diffuse0;

void main() {
    vec3 result = texture(texture_diffuse0, vs_in.TexCoords).rgb;


    FragColor = vec4(result, 1.0);
}