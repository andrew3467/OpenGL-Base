#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 3) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 proj;
uniform mat4 view;
//transform info
uniform mat4 model;


out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    TexCoords = aTexCoord;

    gl_Position = proj * view * vec4(FragPos, 1.0);
}