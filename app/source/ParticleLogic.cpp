#include "ParticleLogic.h"
#include "core/ParticleCanvas.h"

namespace ffass {
void ParticleLogic::Sand(ParticleCanvas& canvas, int index, int x, int y)
{
    auto& buffer = canvas.buffer_;
    auto& particles = canvas.particles_;
    auto& image = canvas.image_;
    int width = image->width;
    int height = image->height;

    int newX = x;
    int newY = y + 1;
    int destIndex = newY * width + newX;

    if (newY < height && particles[destIndex].type == Particle::AIR) {
        buffer[destIndex] = particles[index];
        buffer[index].type = Particle::AIR;

        ImageDrawPixel(image.get(), x, y, Particle::GetColor(buffer[index]));
        ImageDrawPixel(image.get(), newX, newY, Particle::GetColor(particles[index]));
        canvas.dirty_ = true;
        return;
    }

    // Try to move diagonally left and right
    float randomMul = (bool)GetRandomValue(0, 1) ? -1.0f : 1.0f;
    for (int offset = -1; offset <= 1; offset += 2) {
        offset *= randomMul;
        newX = x + offset;
        newY = y + 1;

        if (newX < 0 || newX >= width || newY >= height) {
            continue;
        }

        destIndex = newY * width + newX;

        if (particles[destIndex].type == Particle::AIR && buffer[destIndex].type == Particle::AIR) {
            buffer[destIndex] = particles[index];
            buffer[index].type = Particle::AIR;

            ImageDrawPixel(image.get(), x, y, Particle::GetColor(buffer[index]));
            ImageDrawPixel(image.get(), newX, newY, Particle::GetColor(particles[index]));
            canvas.dirty_ = true;
            return;
        }
    }

    buffer[index] = particles[index];
}

void ParticleLogic::Water(ParticleCanvas& canvas, int index, int x, int y)
{
}
}