#ifndef __PARTICLECANVAS_H__
#define __PARTICLECANVAS_H__

#include <memory>
#include <vector>
#include <cmath>

#include "Particle.h"
#include "ParticleLogic.h"

namespace ffass {
class ParticleCanvas
{
public:
    ParticleCanvas() = default;

    ~ParticleCanvas();

    void init(int particleSize = 4, float interval = 0.1f);

    void draw() const;
    void update(float dt);

    Vector2 screenToCanvas(Vector2 screenPosition) const;

    int canvasToIndex(int x, int y) const;

    void setParticle(int index, Particle::ParticleType type);

    void setParticle(int x, int y, Particle::ParticleType type);

    void forceParticle(int x, int y, Particle::ParticleType type);

    void setPaused(bool paused);

    void setInterval(float interval);

    void setParticleSize(int size);

private:
    void updateDimensions();

    std::vector<Particle> particles_;
    std::vector<Particle> buffer_;
    std::unique_ptr<Image> image_ = nullptr;
    std::unique_ptr<Texture2D> texture_ = nullptr;
    bool dirty_ = false;
    bool paused_ = false;
    float updateInterval_ = 0.1f;
    float updateTimer_ = 0.0f;
    int particleSize_ = 4;

    friend class ParticleLogic;
};
};
#endif // __PARTICLECANVAS_H__