#include "board_logic.h"

void reset_board(GameState *state) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            state->board[row][col] = NONE;
        }
    }

    state->board[0][0] = WHITE_ROOK;
    state->board[0][1] = WHITE_KNIGHT;
    state->board[0][2] = WHITE_BISHOP;
    state->board[0][3] = WHITE_QUEEN;
    state->board[0][4] = WHITE_KING;
    state->board[0][5] = WHITE_BISHOP;
    state->board[0][6] = WHITE_KNIGHT;
    state->board[0][7] = WHITE_ROOK;

    for (int col = 0; col < 8; col++) {
        state->board[1][col] = WHITE_PAWN;
        state->board[6][col] = BLACK_PAWN;
    }

    state->board[7][0] = BLACK_ROOK;
    state->board[7][1] = BLACK_KNIGHT;
    state->board[7][2] = BLACK_BISHOP;
    state->board[7][3] = BLACK_QUEEN;
    state->board[7][4] = BLACK_KING;
    state->board[7][5] = BLACK_BISHOP;
    state->board[7][6] = BLACK_KNIGHT;
    state->board[7][7] = BLACK_ROOK;
}
