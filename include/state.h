#pragma once

#include "conf.h"
#include "raylib.h"
#include "screens/button.h"
#include "utarray.h"
#include <stdbool.h>

#define ROWS 8
#define COLS 8

typedef enum Piece {
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

    INVALID = 12,
    NONE = 13,
} Piece;

typedef struct PieceLocation {
    int row, col;
} PieceLocation;

typedef struct PieceSelection {
    Piece piece;
    PieceLocation pos;
} PieceSelection;

typedef struct PieceCount {
    int pawn, bishop, knight, rook, queen, king;
} PieceCount;

typedef struct PieceMove {
    Piece piece;
    PieceLocation before, after;
} PieceMove;

typedef enum {
    START_MENU,
    GAME,
    END_MENU,
} Scene;

// [row][col]
// [0][0] is bottom left, on white side.
typedef Piece Board[8][8];

typedef struct GameState {
    Conf conf;

    bool running;

    Scene scene;

    int window_x, window_y;
    Vector2 win_offset;
    int win_size;

    struct {
        Board board;

        bool is_piece_selected;
        PieceSelection selected_piece;
        UT_icd valid_moves_icd;
        UT_array *selected_piece_valid_moves;
        PieceMove last_move;

        bool white_to_move, view_as_white;

        struct {
            bool white_king_moved, black_king_moved;
            bool white_a_rook_moved, white_h_rook_moved, black_a_rook_moved,
                black_h_rook_moved;
        } castling;

        PieceSelection promoting;

        PieceCount taken_white_pieces, taken_black_pieces;
    } game;

    struct {
        Button start_button, exit_button;
    } start_screen;

    struct {
        Texture2D board_texture;

        struct {
            Texture2D pawn, bishop, knight, rook, queen, king;
        } white, black;
    } textures;

} GameState;