#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include <cstdint>
#include "raylib.h"

namespace ffass {
struct Particle {
    enum ParticleType : uint8_t { AIR, SAND, STONE, WATER };

    ParticleType type = AIR;

    static Color GetColor(Particle& particle)
    {
        return GetColor(particle.type);
    }

    static Color GetColor(ParticleType ParticleType)
    {
        switch (ParticleType) {
        case Particle::SAND:
            return GOLD;

        case Particle::STONE:
            return GRAY;

        case Particle::WATER:
            return DARKBLUE;

        default:
            return BLACK;
        }
    }

    bool operator==(const Particle& other)
    {
        return this->type == other.type;
    }
    bool operator==(const ParticleType& other)
    {
        return this->type == other;
    }
};
};
#endif // __PARTICLE_H__