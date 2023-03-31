#version 460

#define MAX_POINT_LIGHTS 32
#define MAX_SPOT_LIGHTS 8
#define MAX_DIR_LIGHTS 4

out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;

struct PointLight{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};


uniform vec3 viewPos;
uniform float shininess;
uniform bool blinn;
uniform bool gamma;

uniform int numPointLights;
uniform PointLight pointLights[MAX_POINT_LIGHTS];

uniform sampler2D texture_diffuse0;

vec3 BlinnPhong(vec3 normal, vec3 fragPos, vec3 lightPos, vec3 lightColor)
{
    // diffuse
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * lightColor;
    // specular
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);
    spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular = spec * lightColor;
    // simple attenuation
    float max_distance = 1.5;
    float distance = length(lightPos - fragPos);
    float attenuation = 1.0 / (gamma ? distance * distance : distance);

    diffuse *= attenuation;
    specular *= attenuation;

    return diffuse + specular;
}


void main() {
    vec3 color = texture(texture_diffuse0, fs_in.TexCoords).rgb;
    vec3 lighting = vec3(0.0);

    for(int i = 0; i < numPointLights; i++){
        lighting += BlinnPhong(normalize(fs_in.Normal), fs_in.FragPos, pointLights[i].position, pointLights[i].ambient);
    }
    color *= lighting;

    if(gamma){
        color = pow(color, vec3(1.0 / 2.2));
    }

    FragColor = vec4(color, 1.0);
   //FragColor.rgb = pow(FragColor.rgb, vec3(1.0 / gamma));
}