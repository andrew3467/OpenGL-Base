#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 offset;

uniform mat4 proj;
uniform mat4 view;
//transform info
uniform mat4 model;

void main()
{
    gl_Position = proj * view * model * vec4(aPos + offset, 1.0);
}