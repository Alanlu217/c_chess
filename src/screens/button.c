#include "screens/button.h"

#include "raylib.h"
#include "state.h"

Rectangle getButtonBoundsWin(const Button *b, const GameState *state) {
    return (Rectangle){.x = b->pos.x * state->win_size + state->win_offset.x -
                            b->size.x * state->win_size / 2,
                       .y = b->pos.y * state->win_size + state->win_offset.y -
                            b->size.y * state->win_size / 2,
                       .width = b->size.x * state->win_size,
                       .height = b->size.y * state->win_size};
}

void button_draw(const Button *b, const GameState *state) {
    Rectangle bounds = getButtonBoundsWin(b, state);

    Color button_color;
    if (CheckCollisionPointRec(GetMousePosition(),
                               getButtonBoundsWin(b, state))) {
        button_color = state->conf.button.hover_color;
    } else {
        button_color = state->conf.button.color;
    }

    DrawRectanglePro(bounds, (Vector2){.x = 0, .y = 0}, 0, button_color);

    DrawRectangleLinesEx(bounds, state->conf.button.outline_width,
                         state->conf.button.outline_color);

    int font_size = 40 * state->win_size / 1000;
    int text_size = MeasureText(b->text, font_size);
    DrawText(b->text, bounds.x + bounds.width / 2 - (float)text_size / 2,
             bounds.y + bounds.height / 2 - (float)font_size / 2, font_size,
             WHITE);
}

_Bool button_pressed(const Button *b, const GameState *state) {
    return CheckCollisionPointRec(GetMousePosition(),
                                  getButtonBoundsWin(b, state)) &&
           IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}