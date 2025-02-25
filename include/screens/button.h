#pragma once

#include "conf.h"
#include "raylib.h"

typedef struct {
    Vector2 pos, size;
} Button;

void button_draw(const Button *b, const Conf *c);

_Bool button_pressed(const Button *b);