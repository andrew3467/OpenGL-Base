#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 proj;
uniform mat4 view;
//transform info
uniform mat4 model;

uniform vec3 color;


out vec3 Color;
out vec2 TexCoord;

void main()
{
    gl_Position = proj * view * model * vec4(aPos, 1.0);
    Color = color;
    TexCoord = aTexCoord;
}