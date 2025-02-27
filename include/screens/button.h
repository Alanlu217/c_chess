#pragma once

#include "raylib.h"
#include "state.h"

typedef struct {
    Vector2 pos, size;

    char text[100];
} Button;

void button_draw(const Button *b, const GameState *state);

_Bool button_pressed(const Button *b, const GameState *state);