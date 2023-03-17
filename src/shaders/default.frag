#version 460 core

in vec2 TexCoord;
in vec3 Color;

uniform sampler2D aTexture;

out vec4 FragColor;

void main(){
    FragColor = texture(aTexture, TexCoord);
}