//Source: https://github.com/TheCherno/OneHourParticleSystem/blob/master/OpenGL-Sandbox/src/Random.cpp

#include "Random.h"

std::mt19937 Random::s_RandomEngine;
std::uniform_int_distribution<std::mt19937::result_type> Random::s_Distribution;