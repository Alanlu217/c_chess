#pragma once

#include "conf.h"
#include "raylib.h"
#include <stdbool.h>

typedef enum {
    WHITE_PAWN = 0,
    WHITE_BISHOP = 1,
    WHITE_KNIGHT = 2,
    WHITE_ROOK = 3,
    WHITE_QUEEN = 4,
    WHITE_KING = 5,

    BLACK_PAWN = 6,
    BLACK_BISHOP = 7,
    BLACK_KNIGHT = 8,
    BLACK_ROOK = 9,
    BLACK_QUEEN = 10,
    BLACK_KING = 11,

    NONE = 12,
} Piece;

typedef enum {
    START_MENU,
    GAME,
    END_MENU,
} Scene;

typedef struct {
    Conf conf;

    Scene scene;

    int window_x, window_y;
    Vector2 win_offset;
    int win_size;

    // [row][col]
    // [0][0] is bottom left, on white side.
    Piece board[8][8];

    bool white_to_move;

    struct {

    } start_screen;

    struct {
        Texture2D board_texture;

        struct {
            Texture2D pawn, bishop, knight, rook, queen, king;
        } white, black;
    } textures;

} GameState;