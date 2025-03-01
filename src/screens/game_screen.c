#include "screens/game_screen.h"
#include "raylib.h"
#include "screens/button.h"
#include "state.h"
#include "utarray.h"
#include "win.h"
#include <stdio.h>
#include <time.h>

void reset_board(GameState *state) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            state->game.board[row][col] = NONE;
        }
    }

    state->game.board[0][0] = WHITE_ROOK;
    state->game.board[0][1] = WHITE_KNIGHT;
    state->game.board[0][2] = WHITE_BISHOP;
    state->game.board[0][3] = WHITE_QUEEN;
    state->game.board[0][4] = WHITE_KING;
    state->game.board[0][5] = WHITE_BISHOP;
    state->game.board[0][6] = WHITE_KNIGHT;
    state->game.board[0][7] = WHITE_ROOK;

    for (int col = 0; col < 8; col++) {
        state->game.board[1][col] = WHITE_PAWN;
        state->game.board[6][col] = BLACK_PAWN;
    }

    state->game.board[7][0] = BLACK_ROOK;
    state->game.board[7][1] = BLACK_KNIGHT;
    state->game.board[7][2] = BLACK_BISHOP;
    state->game.board[7][3] = BLACK_QUEEN;
    state->game.board[7][4] = BLACK_KING;
    state->game.board[7][5] = BLACK_BISHOP;
    state->game.board[7][6] = BLACK_KNIGHT;
    state->game.board[7][7] = BLACK_ROOK;

    state->game.white_to_move = true;
    state->game.view_as_white = true;

    state->game.selected_piece_valid_moves = NULL;
}

float calc_game_padding(const GameState *state) {
    return state->win_size * state->conf.game_padding_percent;
}

float calc_square_size(const GameState *state, float game_padding,
                       float board_padding) {
    return (state->win_size - game_padding * 2 - board_padding * 2) / 8;
}

Vector2 piece_coords_to_game(const GameState *state, int row, int col) {
    const float game_padding = calc_game_padding(state);
    const float board_padding = state->conf.board_padding * state->win_size /
                                state->textures.board_texture.height;

    if (state->game.view_as_white) {
        row = 7 - row;
    }

    const float square_size =
        calc_square_size(state, game_padding, board_padding);

    Vector2 final = (Vector2){.x = game_padding + board_padding +
                                   col * square_size + 0.5 * square_size,
                              .y = game_padding + board_padding +
                                   row * square_size + 0.5 * square_size};

    return final;
}

Rectangle piece_coords_to_bounding_box(const GameState *state, int row,
                                       int col) {
    const float game_padding = calc_game_padding(state);
    const float board_padding = state->conf.board_padding * state->win_size /
                                state->textures.board_texture.height;
    const float square_size =
        calc_square_size(state, game_padding, board_padding);

    Vector2 pos = piece_coords_to_game(state, row, col);

    return (Rectangle){.x = pos.x - square_size / 2 + state->win_offset.x,
                       .y = pos.y - square_size / 2 + state->win_offset.y,
                       .width = square_size,
                       .height = square_size};
}

void draw_pieces(const GameState *state) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            Texture2D tex;
            Vector2 offset;

            switch (state->game.board[row][col]) {
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
            default:
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

    Vector2 turn_text_pos =
        game_to_win(state, (Vector2){.x = (float)state->win_size / 2,
                                     .y = game_padding / 2});

    char text[50];
    if (state->game.white_to_move) {
        sprintf(text, "White to play");
    } else {
        sprintf(text, "Black to play");
    }

    int font_size = calc_font_size(60, state);
    float offset = MeasureText(text, font_size);
    DrawText(text, turn_text_pos.x - offset / 2,
             turn_text_pos.y - (float)font_size / 2, font_size, WHITE);

    draw_pieces(state);
}

bool is_white(Piece piece) {
    switch (piece) {
    case WHITE_PAWN:
    case WHITE_BISHOP:
    case WHITE_KNIGHT:
    case WHITE_ROOK:
    case WHITE_QUEEN:
    case WHITE_KING:
        return true;
        break;
    default:
        return false;
        break;
    }
}

bool is_black(Piece piece) {
    switch (piece) {
    case BLACK_PAWN:
    case BLACK_BISHOP:
    case BLACK_KNIGHT:
    case BLACK_ROOK:
    case BLACK_QUEEN:
    case BLACK_KING:
        return true;
        break;
    default:
        return false;
        break;
    }
}

Piece piece_at(GameState *state, int row, int col) {
    if (row < 0 || row > 7 || col < 0 || col > 7) {
        return INVALID;
    }

    return state->game.board[row][col];
}

void check_direction(UT_array *moves, GameState *state, bool white,
                     PieceLocation pos, PieceLocation dir) {
    PieceLocation curr = pos;
    while (true) {
        curr.row += dir.row;
        curr.col += dir.col;

        if (piece_at(state, curr.row, curr.col) == NONE) {
            utarray_push_back(moves, &curr);
            continue;
        }

        if ((white && is_black(piece_at(state, curr.row, curr.col))) ||
            (!white && is_white(piece_at(state, curr.row, curr.col)))) {
            utarray_push_back(moves, &curr);
        }

        break;
    }
}

Piece piece_in_direction(GameState *state, PieceLocation pos,
                         PieceLocation dir) {
    PieceLocation curr = pos;

    while (true) {
        curr.row += dir.row;
        curr.col += dir.col;

        Piece piece = piece_at(state, curr.row, curr.col);

        if (piece != NONE) {
            return piece;
        }
    }
}

UT_array *gen_valid_moves(UT_array *moves, GameState *state,
                          PieceSelection piece);

UT_array *gen_all_moves(GameState *state, bool for_white) {
    UT_array *moves = NULL;
    utarray_new(moves, &state->game.valid_moves_icd);

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            Piece piece = piece_at(state, row, col);
            if ((for_white && is_black(piece)) ||
                (!for_white && is_white(piece)) || piece == BLACK_KING ||
                piece == WHITE_KING) {
                continue;
            }

            gen_valid_moves(moves, state,
                            (PieceSelection){.piece = piece,
                                             .pos = (PieceLocation){
                                                 .row = row, .col = col}});
        }
    }

    return moves;
}

PieceLocation knight_moves[8] = {
    (PieceLocation){.row = 1, .col = 2},
    (PieceLocation){.row = 2, .col = 1},
    (PieceLocation){.row = 2, .col = -1},
    (PieceLocation){.row = 1, .col = -2},
    (PieceLocation){.row = -1, .col = -2},
    (PieceLocation){.row = -2, .col = -1},
    (PieceLocation){.row = -2, .col = 1},
    (PieceLocation){.row = -1, .col = 2},
};

UT_array *gen_valid_moves(UT_array *moves, GameState *state,
                          PieceSelection piece) {
    int prow, pcol;
    prow = piece.pos.row;
    pcol = piece.pos.col;

    PieceLocation pos;

    int white = is_white(piece.piece);
    int forwards = is_white(piece.piece) ? 1 : -1;

    switch (piece.piece) {
    case WHITE_PAWN:
    case BLACK_PAWN:
        if (piece_at(state, prow + forwards, pcol) == NONE) {
            pos.row = prow + forwards;
            pos.col = pcol;
            utarray_push_back(moves, &pos);
        }

        if (((white && prow == 1) || (!white && prow == 6)) &&
            piece_at(state, prow + forwards * 2, pcol) == NONE) {
            pos.row = prow + forwards * 2;
            pos.col = pcol;
            utarray_push_back(moves, &pos);
        }

        if (white && is_black(piece_at(state, prow + 1, pcol + 1))) {
            pos.row = prow + 1;
            pos.col = pcol + 1;
            utarray_push_back(moves, &pos);
        }

        if (white && is_black(piece_at(state, prow + 1, pcol - 1))) {
            pos.row = prow + 1;
            pos.col = pcol - 1;
            utarray_push_back(moves, &pos);
        }

        if (!white && is_white(piece_at(state, prow - 1, pcol + 1))) {
            pos.row = prow - 1;
            pos.col = pcol + 1;
            utarray_push_back(moves, &pos);
        }

        if (!white && is_white(piece_at(state, prow - 1, pcol - 1))) {
            pos.row = prow - 1;
            pos.col = pcol - 1;
            utarray_push_back(moves, &pos);
        }
        break;
    case WHITE_BISHOP:
    case BLACK_BISHOP:
        check_direction(moves, state, white, piece.pos, (PieceLocation){1, 1});
        check_direction(moves, state, white, piece.pos, (PieceLocation){1, -1});
        check_direction(moves, state, white, piece.pos,
                        (PieceLocation){-1, -1});
        check_direction(moves, state, white, piece.pos, (PieceLocation){-1, 1});
        break;
    case WHITE_KNIGHT:
    case BLACK_KNIGHT:
        pos.row = 0; // No declarations after label

        for (int i = 0; i < 8; i++) {
            pos.row = knight_moves[i].row + prow;
            pos.col = knight_moves[i].col + pcol;

            if ((white && is_black(piece_at(state, pos.row, pos.col))) ||
                (!white && is_white(piece_at(state, pos.row, pos.col))) ||
                piece_at(state, pos.row, pos.col) == NONE) {
                utarray_push_back(moves, &pos);
            }
        }
        break;
    case WHITE_ROOK:
    case BLACK_ROOK:
        check_direction(moves, state, white, piece.pos, (PieceLocation){0, 1});
        check_direction(moves, state, white, piece.pos, (PieceLocation){0, -1});
        check_direction(moves, state, white, piece.pos, (PieceLocation){-1, 0});
        check_direction(moves, state, white, piece.pos, (PieceLocation){1, 0});
        break;
    case WHITE_QUEEN:
    case BLACK_QUEEN:
        check_direction(moves, state, white, piece.pos, (PieceLocation){0, 1});
        check_direction(moves, state, white, piece.pos, (PieceLocation){0, -1});
        check_direction(moves, state, white, piece.pos, (PieceLocation){-1, 0});
        check_direction(moves, state, white, piece.pos, (PieceLocation){1, 0});
        check_direction(moves, state, white, piece.pos, (PieceLocation){1, 1});
        check_direction(moves, state, white, piece.pos, (PieceLocation){1, -1});
        check_direction(moves, state, white, piece.pos,
                        (PieceLocation){-1, -1});
        check_direction(moves, state, white, piece.pos, (PieceLocation){-1, 1});
        break;
    case WHITE_KING:
    case BLACK_KING:
        for (int row = -1; row <= 1; row++) {
            for (int col = -1; col <= 1; col++) {
                if (row == 0 && col == 0) {
                    continue;
                }

                PieceLocation board_pos;
                board_pos.row = prow + row;
                board_pos.col = pcol + col;

                Piece piece_in_pos = piece_at(state, prow + row, pcol + col);
                if (piece_in_pos == INVALID ||
                    (white && is_white(piece_in_pos)) ||
                    (!white && is_black(piece_in_pos))) {
                    continue;
                }

                if (white) {
                    if (piece_at(state, board_pos.row + 1, board_pos.col + 1) ==
                        BLACK_PAWN) {
                        continue;
                    }

                    if (piece_at(state, board_pos.row + 1, board_pos.col - 1) ==
                        BLACK_PAWN) {
                        continue;
                    }

                    Piece test_piece;

                    test_piece = piece_in_direction(state, board_pos,
                                                    (PieceLocation){1, 0});
                    if (test_piece == BLACK_ROOK || test_piece == BLACK_QUEEN) {
                        continue;
                    }

                    test_piece = piece_in_direction(state, board_pos,
                                                    (PieceLocation){1, 1});
                    if (test_piece == BLACK_BISHOP ||
                        test_piece == BLACK_QUEEN) {
                        printf("yes");
                        continue;
                    }

                    test_piece = piece_in_direction(state, board_pos,
                                                    (PieceLocation){0, 1});
                    if (test_piece == BLACK_ROOK || test_piece == BLACK_QUEEN) {
                        continue;
                    }

                    test_piece = piece_in_direction(state, board_pos,
                                                    (PieceLocation){-1, 1});
                    if (test_piece == BLACK_BISHOP ||
                        test_piece == BLACK_QUEEN) {
                        continue;
                    }

                    test_piece = piece_in_direction(state, board_pos,
                                                    (PieceLocation){-1, 0});
                    if (test_piece == BLACK_ROOK || test_piece == BLACK_QUEEN) {
                        continue;
                    }

                    test_piece = piece_in_direction(state, board_pos,
                                                    (PieceLocation){-1, -1});
                    if (test_piece == BLACK_BISHOP ||
                        test_piece == BLACK_QUEEN) {
                        continue;
                    }

                    test_piece = piece_in_direction(state, board_pos,
                                                    (PieceLocation){0, -1});
                    if (test_piece == BLACK_ROOK || test_piece == BLACK_QUEEN) {
                        continue;
                    }

                    test_piece = piece_in_direction(state, board_pos,
                                                    (PieceLocation){1, -1});
                    if (test_piece == BLACK_BISHOP ||
                        test_piece == BLACK_QUEEN) {
                        continue;
                    }

                    bool invalid = false;
                    for (int i = 0; i < 8; i++) {
                        pos.row = knight_moves[i].row + board_pos.row;
                        pos.col = knight_moves[i].col + board_pos.col;

                        if (piece_at(state, pos.row, pos.col) == BLACK_KNIGHT) {
                            invalid = true;
                            break;
                        }
                    }
                    if (invalid) {
                        continue;
                    }
                } else {
                    if (piece_at(state, board_pos.row - 1, board_pos.col + 1) ==
                        WHITE_PAWN) {
                        continue;
                    }

                    if (piece_at(state, board_pos.row - 1, board_pos.col - 1) ==
                        WHITE_PAWN) {
                        continue;
                    }

                    Piece test_piece;

                    test_piece = piece_in_direction(state, board_pos,
                                                    (PieceLocation){1, 0});
                    if (test_piece == WHITE_ROOK || test_piece == WHITE_QUEEN) {
                        continue;
                    }

                    test_piece = piece_in_direction(state, board_pos,
                                                    (PieceLocation){1, 1});
                    if (test_piece == WHITE_BISHOP ||
                        test_piece == WHITE_QUEEN) {
                        printf("yes");
                        continue;
                    }

                    test_piece = piece_in_direction(state, board_pos,
                                                    (PieceLocation){0, 1});
                    if (test_piece == WHITE_ROOK || test_piece == WHITE_QUEEN) {
                        continue;
                    }

                    test_piece = piece_in_direction(state, board_pos,
                                                    (PieceLocation){-1, 1});
                    if (test_piece == WHITE_BISHOP ||
                        test_piece == WHITE_QUEEN) {
                        continue;
                    }

                    test_piece = piece_in_direction(state, board_pos,
                                                    (PieceLocation){-1, 0});
                    if (test_piece == WHITE_ROOK || test_piece == WHITE_QUEEN) {
                        continue;
                    }

                    test_piece = piece_in_direction(state, board_pos,
                                                    (PieceLocation){-1, -1});
                    if (test_piece == WHITE_BISHOP ||
                        test_piece == WHITE_QUEEN) {
                        continue;
                    }

                    test_piece = piece_in_direction(state, board_pos,
                                                    (PieceLocation){0, -1});
                    if (test_piece == WHITE_ROOK || test_piece == WHITE_QUEEN) {
                        continue;
                    }

                    test_piece = piece_in_direction(state, board_pos,
                                                    (PieceLocation){1, -1});
                    if (test_piece == WHITE_BISHOP ||
                        test_piece == WHITE_QUEEN) {
                        continue;
                    }

                    bool invalid = false;
                    for (int i = 0; i < 8; i++) {
                        pos.row = knight_moves[i].row + board_pos.row;
                        pos.col = knight_moves[i].col + board_pos.col;

                        if (piece_at(state, pos.row, pos.col) == WHITE_KNIGHT) {
                            invalid = true;
                            break;
                        }
                    }
                    if (invalid) {
                        continue;
                    }
                }

                utarray_push_back(moves, &board_pos);
            }
        }
    default:
        break;
    }

    return moves;
}

bool is_move_valid(UT_array *valid_moves, PieceSelection move) {
    PieceLocation *pos;

    for (pos = (PieceLocation *)utarray_front(valid_moves); pos != NULL;
         pos = (PieceLocation *)utarray_next(valid_moves, pos)) {
        if (pos->col == move.pos.col && pos->row == move.pos.row) {
            return true;
        }
    }

    return false;
}

void select_piece(GameState *state, Piece piece, int row, int col) {
    state->game.selected_piece.piece = state->game.board[row][col];
    state->game.selected_piece.pos.row = row;
    state->game.selected_piece.pos.col = col;

    utarray_clear(state->game.selected_piece_valid_moves);

    state->game.selected_piece_valid_moves = gen_valid_moves(
        state->game.selected_piece_valid_moves, state,
        (PieceSelection){.piece = piece,
                         .pos = (PieceLocation){.row = row, .col = col}});

    state->game.is_piece_selected = true;
}

void deselect(GameState *state) {
    state->game.is_piece_selected = false;

    utarray_clear(state->game.selected_piece_valid_moves);
}

void next_turn(GameState *state) {
    state->game.white_to_move = !state->game.white_to_move;

    deselect(state);
}

void game_screen_init(GameState *state) {
    reset_board(state);
    state->game.is_piece_selected = false;
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

int move_piece(GameState *state, PieceLocation pos) {
    if (state->game.board[pos.row][pos.col] == NONE) {
        state->game.board[state->game.selected_piece.pos.row]
                         [state->game.selected_piece.pos.col] = NONE;
        state->game.board[pos.row][pos.col] = state->game.selected_piece.piece;
        state->game.is_piece_selected = false;
        next_turn(state);
        return 0;
    } else {
        return 1;
    }
}

void update_selection(GameState *state) {
    Vector2 mouse_pos = GetMousePosition();

    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (CheckCollisionPointRec(
                    mouse_pos, piece_coords_to_bounding_box(state, row, col))) {

                if (state->game.is_piece_selected) {
                    if (!move_piece(state, (PieceLocation){row, col})) {
                        break;
                    }
                    deselect(state);
                }

                if (state->game.board[row][col] == NONE ||
                    (state->game.white_to_move &&
                     is_black(state->game.board[row][col])) ||
                    (!state->game.white_to_move &&
                     is_white(state->game.board[row][col]))) {

                    deselect(state);
                    break;
                }

                select_piece(state, state->game.board[row][col], row, col);
            }
        }
    }
}

void game_screen_update(GameState *state) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        update_selection(state);
    }
}

void game_screen_render(const GameState *state) {
    draw_pieces(state);

    draw_board(state);

    if (state->game.is_piece_selected) {
        DrawRectangleLinesEx(piece_coords_to_bounding_box(
                                 state, state->game.selected_piece.pos.row,
                                 state->game.selected_piece.pos.col),
                             state->conf.piece_selection_box.width,
                             state->conf.piece_selection_box.color);
    }

    if (state->game.selected_piece_valid_moves) {
        PieceLocation *pos;

        for (pos = (PieceLocation *)utarray_front(
                 state->game.selected_piece_valid_moves);
             pos != NULL; pos = (PieceLocation *)utarray_next(
                              state->game.selected_piece_valid_moves, pos)) {
            DrawRectangleLinesEx(
                piece_coords_to_bounding_box(state, pos->row, pos->col),
                state->conf.piece_selection_box.width, (Color){0, 0, 255, 255});
        }
    }
}