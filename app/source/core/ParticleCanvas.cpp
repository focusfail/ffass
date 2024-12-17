#include "core/ParticleCanvas.h"

namespace ffass {

ParticleCanvas::~ParticleCanvas()
{
    UnloadImage(*image_);
    UnloadTexture(*texture_);
}

void ParticleCanvas::init(int particleSize, float interval)
{
    this->setInterval(interval);
    this->setParticleSize(particleSize);
    this->updateDimensions();
}

void ParticleCanvas::draw() const
{
    DrawTexturePro(*texture_, { 0.0f, 0.0f, (float)texture_->width, (float)texture_->height },
                   { 0.0f, 0.0f, (float)texture_->width * particleSize_, (float)texture_->height * particleSize_ },
                   { 0.0f }, 0.0f, WHITE);
}

void ParticleCanvas::update(float dt)
{
    if (IsWindowResized()) {
        updateDimensions();
    }

    if (paused_) {
        if (dirty_) {
            UpdateTexture(*texture_, image_->data);
            dirty_ = false;
        }
        return;
    }

    if (updateTimer_ < updateInterval_) {
        updateTimer_ += dt;
        return;
    }

    updateTimer_ = 0.0f;

    const int width = image_->width;
    const int height = image_->height;

    for (int i = particles_.size() - 1; i >= 0; --i) {
        Particle& currPrt = particles_[i];
        int x = i % width;
        int y = i / width;

        if (currPrt.type == Particle::SAND) {
            ParticleLogic::Sand(*this, i, x, y);
        } else if (currPrt.type == Particle::WATER) {
            ParticleLogic::Water(*this, i, x, y);
        } else {
            buffer_[i] = currPrt;
            if (currPrt.type != Particle::AIR) {
                ImageDrawPixel(image_.get(), x, y, Particle::GetColor(currPrt));
            }
        }
    }
    particles_.swap(buffer_);

    if (dirty_) {
        UpdateTexture(*texture_, image_->data);
        dirty_ = false;
    }
}

Vector2 ParticleCanvas::screenToCanvas(Vector2 screenPosition) const
{
    float x = round(screenPosition.x / particleSize_);
    float y = round(screenPosition.y / particleSize_);
    return { x, y };
}

int ParticleCanvas::canvasToIndex(int x, int y) const
{
    return y * image_->width + x;
}

void ParticleCanvas::setParticle(int index, Particle::ParticleType type)
{
    if (index < 0 || index >= particles_.size()) return;

    particles_[index].type = type;
    dirty_ = true;
}

void ParticleCanvas::setParticle(int x, int y, Particle::ParticleType type)
{
    int index = y * image_->width + x;

    if (index < 0 || index >= particles_.size()) return;

    particles_[index].type = type;
    dirty_ = true;
}

void ParticleCanvas::forceParticle(int x, int y, Particle::ParticleType type)
{
    int index = y * image_->width + x;

    if (index < 0 || index >= particles_.size()) return;

    particles_[index].type = type;
    ImageDrawPixel(image_.get(), x, y, Particle::GetColor(type));
    dirty_ = true;
}

void ParticleCanvas::setPaused(bool paused)
{
    paused_ = paused;
}

void ParticleCanvas::setInterval(float interval)
{
    updateInterval_ = interval;
}

void ParticleCanvas::updateDimensions()
{
    const int newWidth = GetScreenWidth() / particleSize_;
    const int newHeight = GetScreenHeight() / particleSize_;

    if (texture_) {
        UnloadTexture(*texture_);
        texture_.reset();
    }
    if (image_) {
        UnloadImage(*image_);
        image_.reset();
    }

    image_ = std::make_unique<Image>(GenImageColor(newWidth, newHeight, Particle::GetColor(Particle::AIR)));
    texture_ = std::make_unique<Texture2D>(LoadTextureFromImage(*image_));

    particles_.resize(newWidth * newHeight, Particle());
    buffer_.resize(newWidth * newHeight, Particle());

    dirty_ = true;
}

void ParticleCanvas::setParticleSize(int size)
{
    particleSize_ = size;
}

};