#ifndef __BRUSH_H__
#define __BRUSH_H__

#include "raylib.h"

#include "core/Particle.h"

namespace ffass {
struct ParticleCanvas;

class Brush
{
public:
    Brush(ParticleCanvas& canvas);

    void line(Vector2 start, Vector2 end, Particle::ParticleType type, int thickness = 1, bool force = false);

private:
    ParticleCanvas* canvas_ = nullptr;
};
};
#endif // __BRUSH_H__