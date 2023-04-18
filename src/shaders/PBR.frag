#version 460

#define PI 3.14159265359
#define MAX_POINT_LIGHTS 32


out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;

uniform sampler2D texture_diffuse;
uniform sampler2D texture_normal;
uniform sampler2D texture_metallic;
uniform sampler2D texture_roughness;
uniform sampler2D texture_ao;

uniform sampler3D cubemap_environment;

uniform float metallic;
uniform float roughness;
uniform float ao;

uniform int numLights;
uniform vec3 lightPositions[MAX_POINT_LIGHTS];
uniform vec3 lightColors[MAX_POINT_LIGHTS];

uniform vec3 viewPos;
uniform bool gamma;


vec3 fresnelSchlick(float cosTheta, vec3 F0){
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

float distributionGGX(vec3 N, vec3 H, float roughness){
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;

    float num = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return num = denom;
}

float geometrySchlickGGX(float NdotV, float roughness){
    float r = (roughness + 1.0);
    float k = (r * r) / 8.0;

    float num = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return num / denom;
}

float geometrySmith(vec3 N, vec3 V, vec3 L, float roughness){
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = geometrySchlickGGX(NdotV, roughness);
    float ggx1 = geometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

void main() {
    vec3 albedo = texture(texture_diffuse, fs_in.TexCoords).rgb;
    vec3 normal = texture(texture_normal, fs_in.TexCoords).rgb;
    float metallic = texture(texture_metallic, fs_in.TexCoords).r;
    float roughness = texture(texture_roughness, fs_in.TexCoords).r;
    float ao = texture(texture_ao, fs_in.TexCoords).r;

    //vec3 N = normalize(fs_in.Normal);
    vec3 N = normalize(normal);
    vec3 V = normalize(viewPos - fs_in.FragPos);

    vec3 Lo = vec3(0.0);
    for (int i = 0; i < numLights; i++) {
        vec3 L = normalize(lightPositions[i] - fs_in.FragPos);
        vec3 H = normalize(V + L);

        float distance = length(lightPositions[i] - fs_in.FragPos);
        float attentuation = 1.0 / (distance * distance);
        vec3 radiance = lightColors[i] * attentuation;

        vec3 F0 = vec3(0.04);
        F0 = mix(F0, albedo, metallic);
        vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0);

        float NDF = distributionGGX(N, H, roughness);
        float G = geometrySmith(N, V, L, roughness);

        vec3 numerator = NDF * G * F;
        float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001;
        vec3 specular = numerator / denominator;

        vec3 ks = F;
        vec3 kD = vec3(1.0) - ks;

        kD *= metallic;

        float NdotL = max(dot(N, L), 0.0);
        Lo += (kD * albedo / PI + specular) * radiance * NdotL;
    }

    vec3 ambient = vec3(0.03) * albedo * ao;
    vec3 color = ambient + Lo;

    if(gamma){
        color = color / (color + vec3(1.0));
        color = pow(color, vec3(1.0/2.2));
    }

    FragColor = vec4(color, 1.0);
}