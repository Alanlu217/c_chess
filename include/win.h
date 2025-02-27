#pragma once

#include "raylib.h"
#include "screens/button.h"
#include "state.h"

void update_window_state(GameState *state);

Vector2 win_to_game(const GameState *state, Vector2 win);

Vector2 game_to_win(const GameState *state, Vector2 game);

int calc_font_size(int size, const GameState *state);