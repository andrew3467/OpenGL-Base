//
// Created by Andrew Graser on 4/20/2023.
//

#include "ParticleEmitter.h"
#include "renderer/Renderer.h"
#include "Random.h"
#include <random>

#include <glm/gtx/functions.hpp>


ParticleEmitter::ParticleEmitter(const std::string texPath, glm::vec3 position, unsigned int cacheSize) : texPath(texPath), position(position) {
    particlePool.resize(cacheSize);
    poolIndex = cacheSize - 1;

    particleTexture = std::make_unique<Texture2D>(texPath);

    particleShader = std::make_unique<Shader>("../../src/shaders/Particle.vert", "../../src/shaders/Particle.frag");
}

void ParticleEmitter::Draw(const glm::mat4& viewproj, glm::vec3 camPos, glm::vec3 camUp) {
    for(auto& particle : particlePool){
        if(!particle.Active){
            continue;
        }

        particleShader->Bind();

        float life = particle.LifeRemaining / particle.LifeTime;
        float size = glm::mix(particle.SizeEnd, particle.SizeBegin, life);
        glm::vec4 color = glm::mix(particle.ColorEnd, particle.ColorBegin, life);
        color.a *= life;

        glm::mat4 model = glm::translate(glm::mat4(1.0f), particle.Position);
        model = glm::scale(model, glm::vec3(size));

        particleShader->SetMat4("mvp", viewproj * model);

        particleShader->SetVec4("color", color);

        particleTexture->Bind();
        particleShader->SetInt("sprite", 0);

        Renderer::DrawQuad(*particleShader);
    }
}

void ParticleEmitter::UpdateParticles(float deltaTime) {
    for(auto& particle : particlePool){
        if(!particle.Active){
            continue;
        }

        if(particle.LifeRemaining <= 0.0f){
            particle.Active = false;
            continue;
        }

        particle.LifeRemaining -= deltaTime;
        particle.Position += particle.Velocity * deltaTime;
        particle.Rotation += 0.01f * deltaTime;
    }
}

void ParticleEmitter::Emit(const ParticleProps& config) {
    auto& particle = particlePool[poolIndex];

    particle.Active = true;
    particle.Position = config.Position + position;
    particle.Rotation = Random::Float() * 2.0f * glm::pi<float>();

    particle.Velocity = config.Velocity;
    particle.Velocity.x += config.VelocityVariation.x * (Random::Float() - 0.5f);
    particle.Velocity.y += config.VelocityVariation.y * (Random::Float() - 0.5f);
    particle.Velocity.z += config.VelocityVariation.z * (Random::Float() - 0.5f);
    particle.Velocity.y = particle.Velocity.y * particle.Velocity.y - particle.Velocity.y;

    particle.ColorBegin = config.ColorBegin;
    particle.ColorEnd = config.ColorEnd;

    particle.LifeTime = config.LifeTime;
    particle.LifeRemaining = particle.LifeTime;
    particle.SizeBegin = config.SizeBegin + config.SizeVariation * (Random::Float() - 0.5f);
    particle.SizeEnd = config.SizeEnd;

    poolIndex = --poolIndex % particlePool.size();
}
