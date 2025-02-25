#include "win.h"
#include "raylib.h"
#include "raymath.h"

void update_window_state(GameState *state) {
    state->window_x = GetScreenWidth();
    state->window_y = GetScreenHeight();

    if (state->window_x < state->window_y) {
        state->win_size = state->window_x;

        state->win_offset.x = 0;
        state->win_offset.y = (float)(state->window_y - state->win_size) / 2;
    } else {
        state->win_size = state->window_y;

        state->win_offset.y = 0;
        state->win_offset.x = (float)(state->window_x - state->win_size) / 2;
    }
}

Vector2 win_to_game(const GameState *state, Vector2 win) {
    return Vector2Subtract(win, state->win_offset);
}

Vector2 game_to_win(const GameState *state, Vector2 game) {
    return Vector2Add(game, state->win_offset);
}