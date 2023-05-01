//
// Created by Andrew Graser on 4/20/2023.
//

#ifndef OPENGL_BASE_PARTICLEEMITTER_H
#define OPENGL_BASE_PARTICLEEMITTER_H

#include <glm/glm.hpp>
#include <vector>
#include <functional>
#include "renderer/Shader.h"
#include "renderer/VertexArray.h"
#include "renderer/IndexBuffer.h"
#include "renderer/Texture2D.h"


struct Particle {
    glm::vec3 Position, Velocity;
    glm::vec4 ColorBegin, ColorEnd;

    float Rotation;
    float LifeTime;
    float LifeRemaining;

    float SizeBegin, SizeEnd;
    bool Active;

    Particle() : Position(0.0f), Velocity(0.0f), ColorBegin(1.0f), ColorEnd(0.0f), LifeTime(0.0f), SizeBegin(1.0f), SizeEnd(0.0f), Active(false) {
        LifeRemaining = LifeTime;

    }
};

struct ParticleProps{
    glm::vec3 Position, Velocity, VelocityVariation;
    glm::vec4 ColorBegin, ColorEnd;

    float Rotation;
    float LifeTime;

    float SizeBegin, SizeEnd;
    float SizeVariation;
};

class ParticleEmitter {
public:
    ParticleEmitter(std::string texPath, glm::vec3 position = glm::vec3(0.0f), unsigned int cacheSize = 512);

private:
    glm::vec3 position;
    std::string texPath;

    std::vector<Particle> particlePool;
    unsigned int poolIndex;

    std::unique_ptr<Shader> particleShader;
    std::unique_ptr<Texture2D> particleTexture;

public:
    void Draw(const glm::mat4& viewproj, glm::vec3 camPos, glm::vec3 camUp);
    void UpdateParticles(float deltaTime);
    void Emit(const ParticleProps& config);
};


#endif //OPENGL_BASE_PARTICLEEMITTER_H
