#include "state.h"

void reset_board(GameState *state);

void load_textures(GameState *state);

float calc_game_padding(const GameState *state);

Vector2 piece_coords_to_game(const GameState *state, int row, int col);

void draw_pieces(const GameState *state);

void draw_board(const GameState *state);

void game_screen_update(GameState *state);

void game_screen_render(const GameState *state);