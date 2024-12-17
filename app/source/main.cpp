#include <iostream>
#include <cstdint>
#include <vector>
#include <cassert>
#include <memory>

#include "raylib.h"
#include "raymath.h"

#include "core/ParticleCanvas.h"
#include "Brush.h"

using ffass::Particle;

int main(int argc, char const* argv[])
{
    std::cout << "Hello, World!";

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_ALWAYS_RUN);
    InitWindow(800, 600, "focusfail's advanced sand simulator");
    SetWindowIcon(LoadImage("./assets/ffass.png"));

    ffass::ParticleCanvas canvas;
    canvas.init(10, 1 / 100.0f);

    ffass::Brush brush(canvas);

    float updateTO = 0.0;
    bool paused = false;
    Vector2 previous = { 0.0f, 0.0f };

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        Vector2 mp = GetMousePosition();
        auto [x, y] = canvas.screenToCanvas(mp);
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            brush.line(previous, { x, y }, Particle::SAND, 2);
            // canvas.setParticle(x, y, Particle::SAND);
        } else if (IsMouseButtonDown(MOUSE_MIDDLE_BUTTON)) {
            brush.line(previous, { x, y }, Particle::AIR, 2, true);
            paused = true;
        } else if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
            brush.line(previous, { x, y }, Particle::STONE, 2);
        } else if (IsKeyDown(KEY_W)) {
            canvas.setParticle(x, y, Particle::WATER);
        } else {
            paused = false;
        }
        previous = { x, y };

        canvas.update(dt);

        canvas.setPaused(paused);

        BeginDrawing();
        ClearBackground(BLACK);

        canvas.draw();

        DrawFPS(10, 10);
        EndDrawing();
    }
}