#pragma once

#include "raylib.h"

typedef struct Conf {
    float game_padding_percent;
    float board_padding;
    float piece_scale;
    float taken_piece_scale;

    struct {
        Vector2 white_pawn;
        Vector2 white_bishop;
        Vector2 white_knight;
        Vector2 white_rook;
        Vector2 white_queen;
        Vector2 white_king;

        Vector2 black_pawn;
        Vector2 black_bishop;
        Vector2 black_knight;
        Vector2 black_rook;
        Vector2 black_queen;
        Vector2 black_king;
    } piece_offsets;

    struct {
        Color color;
        Color hover_color;
        Color outline_color;

        float outline_width;
    } button;

    struct {
        Color color;
        float width;
    } piece_selection_box;

    struct {
        float x_pc, y_pc, y_pc_factor;
    } taken_piece_offsets;
} Conf;

int conf_load(Conf *conf);