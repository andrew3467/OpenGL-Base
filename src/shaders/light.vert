#version 460 core
layout (location = 0) in vec3 aPos;

uniform mat4 proj;
uniform mat4 view;
//transform info
uniform mat4 model;

void main()
{
    gl_Position = proj * view * model * vec4(aPos, 1.0);
}