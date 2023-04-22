#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;


uniform mat4 mvp;

void main() {
    TexCoord = aTexCoord;

    float scale = 0.5f;
    gl_Position = mvp * vec4(aPos, 1.0);
}