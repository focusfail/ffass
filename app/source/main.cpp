#include <iostream>
#include <cstdint>
#include <vector>
#include <cassert>
#include <memory>

#include "raylib.h"
#include "raymath.h"

#include "ParticleCanvas.h"
#include "Brush.h"

int main(int argc, char const* argv[])
{
    std::cout << "Hello, World!";

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "focusfail's advanced sand simulator");
    SetWindowIcon(LoadImage("./app/assets/ffass.png"));

    ParticleCanvas canvas;
    canvas.setInterval(1 / 1000.0f);

    Brush brush(canvas);

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