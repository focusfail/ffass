#ifndef __PARTICLECANVAS_H__
#define __PARTICLECANVAS_H__

#include <memory>
#include <vector>
#include <cmath>

#include "Particle.h"
#include "ParticleLogic.h"

class ParticleCanvas
{
public:
    ParticleCanvas()
    {
        updateDimensions();
    }

    ~ParticleCanvas()
    {
        UnloadImage(*image_);
        UnloadTexture(*texture_);
    }

    inline void draw() const
    {
        DrawTexturePro(
            *texture_, { 0.0f, 0.0f, (float)texture_->width, (float)texture_->height },
            { 0.0f, 0.0f, (float)texture_->width * Particle::Size, (float)texture_->height * Particle::Size }, { 0.0f },
            0.0f, WHITE);
    }

    inline void update(float dt)
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

    inline Vector2 screenToCanvas(Vector2 screenPosition) const
    {
        float x = round(screenPosition.x / Particle::Size);
        float y = round(screenPosition.y / Particle::Size);
        return { x, y };
    }

    inline int canvasToIndex(int x, int y) const
    {
        return y * image_->width + x;
    }

    inline void setParticle(int index, Particle::ParticleType type)
    {
        if (index < 0 || index >= particles_.size()) return;

        particles_[index].type = type;
        dirty_ = true;
    }

    inline void setParticle(int x, int y, Particle::ParticleType type)
    {
        int index = y * image_->width + x;

        if (index < 0 || index >= particles_.size()) return;

        particles_[index].type = type;
        dirty_ = true;
    }

    inline void forceParticle(int x, int y, Particle::ParticleType type)
    {
        int index = y * image_->width + x;

        if (index < 0 || index >= particles_.size()) return;

        particles_[index].type = type;
        ImageDrawPixel(image_.get(), x, y, Particle::GetColor(type));
        dirty_ = true;
    }

    inline void setPaused(bool paused)
    {
        paused_ = paused;
    }

    inline void setInterval(float interval)
    {
        updateInterval_ = interval;
    }

private:
    inline void updateDimensions()
    {
        const int newWidth = GetScreenWidth() / Particle::Size;
        const int newHeight = GetScreenHeight() / Particle::Size;

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

    std::vector<Particle> particles_;
    std::vector<Particle> buffer_;
    std::unique_ptr<Image> image_ = nullptr;
    std::unique_ptr<Texture2D> texture_ = nullptr;
    bool dirty_ = false;
    bool paused_ = false;
    float updateInterval_ = 0.1f;
    float updateTimer_ = 0.0f;

    friend class ParticleLogic;
};

#endif // __PARTICLECANVAS_H__