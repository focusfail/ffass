#include "Brush.h"

#include "raymath.h"

#include "ParticleCanvas.h"

Brush::Brush(ParticleCanvas& canvas)
    : canvas_(&canvas)
{
}

void Brush::line(Vector2 start, Vector2 end, Particle::ParticleType type, int thickness, bool force)
{
    int startX = std::min(start.x, end.x);
    int startY = std::min(start.y, end.y);
    int endX = std::max(start.x, end.x);
    int endY = std::max(start.y, end.y);

    int halfThickness = static_cast<int>(thickness / 2 + 0.5);

    for (int x = startX - halfThickness; x <= endX + halfThickness; x++) {
        for (int y = startY - halfThickness; y <= endY + halfThickness; y++) {
            int index = canvas_->canvasToIndex(x, y);
            if (force) {
                canvas_->forceParticle(x, y, type);
                continue;
            }
            canvas_->setParticle(index, type);
        }
    }
}