#include <stdio.h>
#include "ffass.h"

int main(int argc, char const *argv[])
{   
    printf("Hello, World!");

    InitWindow(800, 600, "Test");

    PCanvas* canvas = canvas_gen(800, 600);

    while(!WindowShouldClose())
    {
        Vector2 mouse_pos = GetMousePosition();

        canvas_put(canvas, mouse_pos.x, mouse_pos.y, AIR);
        canvas_update(canvas);
        BeginDrawing();

        ClearBackground(BLACK);

        canvas_draw(canvas);

        EndDrawing();
    }

    canvas_destroy(canvas);
    
    return 0;
}
