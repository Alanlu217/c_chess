#include "screens/game_screen.h"
#include "win.h"

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

    state->white_to_move = true;
}

void load_textures(GameState *state) {
    state->textures.board_texture = LoadTexture("assets/board.png");

    state->textures.black.pawn = LoadTexture("assets/black_pawn.png");
    state->textures.black.bishop = LoadTexture("assets/black_bishop.png");
    state->textures.black.knight = LoadTexture("assets/black_knight.png");
    state->textures.black.rook = LoadTexture("assets/black_rook.png");
    state->textures.black.queen = LoadTexture("assets/black_queen.png");
    state->textures.black.king = LoadTexture("assets/black_king.png");

    state->textures.white.pawn = LoadTexture("assets/white_pawn.png");
    state->textures.white.bishop = LoadTexture("assets/white_bishop.png");
    state->textures.white.knight = LoadTexture("assets/white_knight.png");
    state->textures.white.rook = LoadTexture("assets/white_rook.png");
    state->textures.white.queen = LoadTexture("assets/white_queen.png");
    state->textures.white.king = LoadTexture("assets/white_king.png");
}

float calc_game_padding(const GameState *state) {
    return state->win_size * state->conf.game_padding_percent;
}

Vector2 piece_coords_to_game(const GameState *state, int row, int col) {
    const float game_padding = calc_game_padding(state);
    const float board_padding = state->conf.board_padding * state->win_size /
                                state->textures.board_texture.height;

    if (state->white_to_move) {
        row = 7 - row;
    }

    const float square_size =
        (state->win_size - game_padding * 2 - board_padding * 2) / 8;

    Vector2 final = (Vector2){.x = game_padding + board_padding +
                                   col * square_size + 0.5 * square_size,
                              .y = game_padding + board_padding +
                                   row * square_size + 0.5 * square_size};

    return final;
}

void draw_pieces(const GameState *state) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            Texture2D tex;
            Vector2 offset;

            switch (state->board[row][col]) {
            case WHITE_PAWN:
                tex = state->textures.white.pawn;
                offset = state->conf.piece_offsets.white_pawn;
                break;
            case WHITE_BISHOP:
                tex = state->textures.white.bishop;
                offset = state->conf.piece_offsets.white_bishop;
                break;
            case WHITE_KNIGHT:
                tex = state->textures.white.knight;
                offset = state->conf.piece_offsets.white_knight;
                break;
            case WHITE_ROOK:
                tex = state->textures.white.rook;
                offset = state->conf.piece_offsets.white_rook;
                break;
            case WHITE_QUEEN:
                tex = state->textures.white.queen;
                offset = state->conf.piece_offsets.white_queen;
                break;
            case WHITE_KING:
                tex = state->textures.white.king;
                offset = state->conf.piece_offsets.white_king;
                break;
            case BLACK_PAWN:
                tex = state->textures.black.pawn;
                offset = state->conf.piece_offsets.black_pawn;
                break;
            case BLACK_BISHOP:
                tex = state->textures.black.bishop;
                offset = state->conf.piece_offsets.black_bishop;
                break;
            case BLACK_KNIGHT:
                tex = state->textures.black.knight;
                offset = state->conf.piece_offsets.black_knight;
                break;
            case BLACK_ROOK:
                tex = state->textures.black.rook;
                offset = state->conf.piece_offsets.black_rook;
                break;
            case BLACK_QUEEN:
                tex = state->textures.black.queen;
                offset = state->conf.piece_offsets.black_queen;
                break;
            case BLACK_KING:
                tex = state->textures.black.king;
                offset = state->conf.piece_offsets.black_king;
                break;
            case NONE:
                continue;
            }

            const Vector2 pos =
                game_to_win(state, piece_coords_to_game(state, row, col));

            float scale = (float)state->win_size * state->conf.piece_scale;

            DrawTexturePro(
                tex,
                (Rectangle){
                    .x = 0, .y = 0, .height = tex.height, .width = tex.width},
                (Rectangle){.x = pos.x + offset.x * state->win_size,
                            .y = pos.y + offset.y * state->win_size,
                            .height = tex.height * scale,
                            .width = tex.width * scale},
                (Vector2){.x = ((float)tex.height * scale) / 2,
                          .y = ((float)tex.width * scale) / 2},
                0, WHITE);
        }
    }
}

void draw_board(const GameState *state) {
    Vector2 pos = game_to_win(state, (Vector2){0, 0});

    const float game_padding = calc_game_padding(state);

    DrawTexturePro(state->textures.board_texture,
                   (Rectangle){.height = 180, .width = 180, .x = 0, .y = 0},
                   (Rectangle){.height = state->win_size - game_padding * 2,
                               .width = state->win_size - game_padding * 2,
                               .x = pos.x + game_padding,
                               .y = pos.y + game_padding},
                   (Vector2){0, 0}, 0, WHITE);

    draw_pieces(state);
}