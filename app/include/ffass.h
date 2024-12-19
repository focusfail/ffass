#ifndef __FFASS_H__
#define __FFASS_H__

#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"

typedef enum {AIR, SAND} PType;

struct _Particle{
    PType type;
} _Particle = {0}; 

typedef struct _Particle Particle;

typedef struct {
    Particle* back;
    Particle* front;
    Image img;
    Texture2D tex;
} PCanvas;

PCanvas* canvas_gen(int width, int height) {
    PCanvas* canvas = (PCanvas*)malloc(sizeof(PCanvas));
    canvas->img = GenImageColor(width, height, PINK);
    canvas->tex = LoadTextureFromImage(canvas->img);
    int capacity = width * height;
    canvas->back = (Particle*)malloc(capacity * sizeof(Particle));
    canvas->front = (Particle*)malloc(capacity * sizeof(Particle));

    return canvas;
}

void canvas_destroy(PCanvas* canvas)
{
    UnloadTexture(canvas->tex);
    UnloadImage(canvas->img);

    free(canvas->back);
    free(canvas->front);
    canvas->back = NULL;
    canvas->front = NULL;

    free(canvas);
    canvas = NULL; 
}

void canvas_put(PCanvas* canvas, int x, int y, PType type)
{
    int index = y * canvas->img.width + x; 
    canvas->front[index].type = type;
}

void canvas_update(PCanvas* canvas)
{
    int cap = canvas->img.width * canvas->img.height;
    for (int i = 0; i < cap; i++)
    {
        int x = i % canvas->img.width;
        int y = i / canvas->img.width;

        ImageDrawPixel(&canvas->img, x, y, );
    }
    UpdateTexture(canvas->tex, canvas->img.data);
}

void canvas_draw(const PCanvas* canvas)
{
    int width = GetScreenWidth(), height = GetScreenHeight();
    DrawTexture(canvas->tex, 0 ,0, WHITE);
}

#endif __FFASS_H__