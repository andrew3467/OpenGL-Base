#version 460

#define MAX_POINT_LIGHTS 32

out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;

uniform sampler2D texture_diffuse0;

uniform int numLights;
uniform vec3 lightPositions[MAX_POINT_LIGHTS];
uniform vec3 lightColors[MAX_POINT_LIGHTS];
uniform vec3 viewPos;
uniform bool gamma;


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
    float dist = length(lightPos - fragPos);
    float attenuation = 1.0 / (gamma ? dist * dist : dist);

    return diffuse + specular;

    diffuse *= attenuation;
    specular *= attenuation;

    return diffuse + specular;
}

void main()
{
    vec3 color = texture(texture_diffuse0, fs_in.TexCoords).rgb;
    vec3 lighting = vec3(0.0);

    for(int i = 0; i < numLights; ++i) {
        lighting += BlinnPhong(normalize(fs_in.Normal),
                               fs_in.FragPos,
                               lightPositions[i],
                               lightColors[i]);
    }

    color *= lighting;

    if(gamma) {
        color = pow(color, vec3(1.0 / 2.2));
    }

    FragColor = vec4(color, 1.0);
}