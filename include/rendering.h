#pragma once

#include "raylib.h"
#include "state.h"

void load_textures(GameState *state);

float calc_game_padding(const GameState *state);

Vector2 piece_coords_to_win(const GameState *state, int row, int col);

void draw_pieces(const GameState *state);

void draw_board(const GameState *state);