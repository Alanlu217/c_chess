#include "screens/button.h"
#include "raylib.h"

void button_draw(const Button *b, const Conf *c) {
    DrawRectanglePro((Rectangle){.x = b->pos.x,
                                 .y = b->pos.y,
                                 .width = b->size.x,
                                 .height = b->size.y},
                     (Vector2){.x = b->size.x / 2, .y = b->size.y / 2}, 0,
                     c->button_color);
}

_Bool button_pressed(const Button *b) {}