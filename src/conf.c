#include "conf.h"
#include "toml.h"
#include <stdio.h>

int conf_load(Conf *conf) {
    char errbuf[200];

    FILE *fp = fopen("assets/conf.toml", "r");
    toml_table_t *tb = toml_parse_file(fp, errbuf, sizeof(errbuf));

    toml_table_t *board = toml_table_table(tb, "board");

    toml_value_t game_padding = toml_table_double(board, "padding_pc");
    if (!game_padding.ok) {
        return 1;
    }
    conf->game_padding_percent = game_padding.u.d;

    toml_value_t board_padding = toml_table_double(board, "edge_padding");
    if (!board_padding.ok) {
        return 1;
    }
    conf->board_padding = board_padding.u.d;

    toml_value_t piece_scale = toml_table_double(board, "piece_scale");
    if (!piece_scale.ok) {
        return 1;
    }
    conf->piece_scale = piece_scale.u.d;

    toml_value_t taken_piece_scale =
        toml_table_double(board, "taken_piece_scale");
    if (!taken_piece_scale.ok) {
        return 1;
    }
    conf->taken_piece_scale = taken_piece_scale.u.d;

    // Get piece offsets
    {
        toml_table_t *white_offsets =
            toml_table_table(tb, "white_piece_offsets");

        toml_table_t *white_pawn = toml_table_table(white_offsets, "pawn");
        toml_value_t white_pawn_x = toml_table_double(white_pawn, "x");
        if (!white_pawn_x.ok) {
            return 1;
        }
        conf->piece_offsets.white_pawn.x = white_pawn_x.u.d;
        toml_value_t white_pawn_y = toml_table_double(white_pawn, "y");
        if (!white_pawn_y.ok) {
            return 1;
        }
        conf->piece_offsets.white_pawn.y = white_pawn_y.u.d;

        toml_table_t *white_bishop = toml_table_table(white_offsets, "bishop");
        toml_value_t white_bishop_x = toml_table_double(white_bishop, "x");
        if (!white_bishop_x.ok) {
            return 1;
        }
        conf->piece_offsets.white_bishop.x = white_bishop_x.u.d;
        toml_value_t white_bishop_y = toml_table_double(white_bishop, "y");
        if (!white_bishop_y.ok) {
            return 1;
        }
        conf->piece_offsets.white_bishop.y = white_bishop_y.u.d;

        toml_table_t *white_knight = toml_table_table(white_offsets, "knight");
        toml_value_t white_knight_x = toml_table_double(white_knight, "x");
        if (!white_knight_x.ok) {
            return 1;
        }
        conf->piece_offsets.white_knight.x = white_knight_x.u.d;
        toml_value_t white_knight_y = toml_table_double(white_knight, "y");
        if (!white_knight_y.ok) {
            return 1;
        }
        conf->piece_offsets.white_knight.y = white_knight_y.u.d;

        toml_table_t *white_rook = toml_table_table(white_offsets, "rook");
        toml_value_t white_rook_x = toml_table_double(white_rook, "x");
        if (!white_rook_x.ok) {
            return 1;
        }
        conf->piece_offsets.white_rook.x = white_rook_x.u.d;
        toml_value_t white_rook_y = toml_table_double(white_rook, "y");
        if (!white_rook_y.ok) {
            return 1;
        }
        conf->piece_offsets.white_rook.y = white_rook_y.u.d;

        toml_table_t *white_queen = toml_table_table(white_offsets, "queen");
        toml_value_t white_queen_x = toml_table_double(white_queen, "x");
        if (!white_queen_x.ok) {
            return 1;
        }
        conf->piece_offsets.white_queen.x = white_queen_x.u.d;
        toml_value_t white_queen_y = toml_table_double(white_queen, "y");
        if (!white_queen_y.ok) {
            return 1;
        }
        conf->piece_offsets.white_queen.y = white_queen_y.u.d;

        toml_table_t *white_king = toml_table_table(white_offsets, "king");
        toml_value_t white_king_x = toml_table_double(white_king, "x");
        if (!white_king_x.ok) {
            return 1;
        }
        conf->piece_offsets.white_king.x = white_king_x.u.d;
        toml_value_t white_king_y = toml_table_double(white_king, "y");
        if (!white_king_y.ok) {
            return 1;
        }
        conf->piece_offsets.white_king.y = white_king_y.u.d;

        toml_table_t *black_offsets =
            toml_table_table(tb, "black_piece_offsets");

        toml_table_t *black_pawn = toml_table_table(black_offsets, "pawn");
        toml_value_t black_pawn_x = toml_table_double(black_pawn, "x");
        if (!black_pawn_x.ok) {
            return 1;
        }
        conf->piece_offsets.black_pawn.x = black_pawn_x.u.d;
        toml_value_t black_pawn_y = toml_table_double(black_pawn, "y");
        if (!black_pawn_y.ok) {
            return 1;
        }
        conf->piece_offsets.black_pawn.y = black_pawn_y.u.d;

        toml_table_t *black_bishop = toml_table_table(black_offsets, "bishop");
        toml_value_t black_bishop_x = toml_table_double(black_bishop, "x");
        if (!black_bishop_x.ok) {
            return 1;
        }
        conf->piece_offsets.black_bishop.x = black_bishop_x.u.d;
        toml_value_t black_bishop_y = toml_table_double(black_bishop, "y");
        if (!black_bishop_y.ok) {
            return 1;
        }
        conf->piece_offsets.black_bishop.y = black_bishop_y.u.d;

        toml_table_t *black_knight = toml_table_table(black_offsets, "knight");
        toml_value_t black_knight_x = toml_table_double(black_knight, "x");
        if (!black_knight_x.ok) {
            return 1;
        }
        conf->piece_offsets.black_knight.x = black_knight_x.u.d;
        toml_value_t black_knight_y = toml_table_double(black_knight, "y");
        if (!black_knight_y.ok) {
            return 1;
        }
        conf->piece_offsets.black_knight.y = black_knight_y.u.d;

        toml_table_t *black_rook = toml_table_table(black_offsets, "rook");
        toml_value_t black_rook_x = toml_table_double(black_rook, "x");
        if (!black_rook_x.ok) {
            return 1;
        }
        conf->piece_offsets.black_rook.x = black_rook_x.u.d;
        toml_value_t black_rook_y = toml_table_double(black_rook, "y");
        if (!black_rook_y.ok) {
            return 1;
        }
        conf->piece_offsets.black_rook.y = black_rook_y.u.d;

        toml_table_t *black_queen = toml_table_table(black_offsets, "queen");
        toml_value_t black_queen_x = toml_table_double(black_queen, "x");
        if (!black_queen_x.ok) {
            return 1;
        }
        conf->piece_offsets.black_queen.x = black_queen_x.u.d;
        toml_value_t black_queen_y = toml_table_double(black_queen, "y");
        if (!black_queen_y.ok) {
            return 1;
        }
        conf->piece_offsets.black_queen.y = black_queen_y.u.d;

        toml_table_t *black_king = toml_table_table(black_offsets, "king");
        toml_value_t black_king_x = toml_table_double(black_king, "x");
        if (!black_king_x.ok) {
            return 1;
        }
        conf->piece_offsets.black_king.x = black_king_x.u.d;
        toml_value_t black_king_y = toml_table_double(black_king, "y");
        if (!black_king_y.ok) {
            return 1;
        }
        conf->piece_offsets.black_king.y = black_king_y.u.d;
    }

    toml_table_t *button = toml_table_table(tb, "button");

    toml_table_t *button_color = toml_table_table(button, "color");

    toml_value_t r = toml_table_int(button_color, "r");
    if (!r.ok) {
        return 1;
    }
    conf->button.color.r = r.u.i;

    toml_value_t g = toml_table_int(button_color, "g");
    if (!g.ok) {
        return 1;
    }
    conf->button.color.g = g.u.i;

    toml_value_t b = toml_table_int(button_color, "b");
    if (!b.ok) {
        return 1;
    }
    conf->button.color.b = b.u.i;

    toml_value_t a = toml_table_int(button_color, "a");
    if (!a.ok) {
        return 1;
    }
    conf->button.color.a = a.u.i;

    toml_table_t *button_hover_color = toml_table_table(button, "hover_color");

    r = toml_table_int(button_hover_color, "r");
    if (!r.ok) {
        return 1;
    }
    conf->button.hover_color.r = r.u.i;

    g = toml_table_int(button_hover_color, "g");
    if (!g.ok) {
        return 1;
    }
    conf->button.hover_color.g = g.u.i;

    b = toml_table_int(button_hover_color, "b");
    if (!b.ok) {
        return 1;
    }
    conf->button.hover_color.b = b.u.i;

    a = toml_table_int(button_hover_color, "a");
    if (!a.ok) {
        return 1;
    }
    conf->button.hover_color.a = a.u.i;

    toml_table_t *button_outline_color =
        toml_table_table(button, "outline_color");

    r = toml_table_int(button_outline_color, "r");
    if (!r.ok) {
        return 1;
    }
    conf->button.outline_color.r = r.u.i;

    g = toml_table_int(button_outline_color, "g");
    if (!g.ok) {
        return 1;
    }
    conf->button.outline_color.g = g.u.i;

    b = toml_table_int(button_outline_color, "b");
    if (!b.ok) {
        return 1;
    }
    conf->button.outline_color.b = b.u.i;

    a = toml_table_int(button_outline_color, "a");
    if (!a.ok) {
        return 1;
    }
    conf->button.outline_color.a = a.u.i;

    toml_value_t button_outline_width = toml_table_double(button, "width");
    if (!button_outline_width.ok) {
        return 1;
    }
    conf->button.outline_width = button_outline_width.u.d;

    toml_table_t *piece_selection = toml_table_table(tb, "piece_selection");

    toml_table_t *piece_selection_color =
        toml_table_table(piece_selection, "color");

    r = toml_table_int(piece_selection_color, "r");
    if (!r.ok) {
        return 1;
    }
    conf->piece_selection_box.color.r = r.u.i;

    g = toml_table_int(piece_selection_color, "g");
    if (!g.ok) {
        return 1;
    }
    conf->piece_selection_box.color.g = g.u.i;

    b = toml_table_int(piece_selection_color, "b");
    if (!b.ok) {
        return 1;
    }
    conf->piece_selection_box.color.b = b.u.i;

    a = toml_table_int(piece_selection_color, "a");
    if (!a.ok) {
        return 1;
    }
    conf->piece_selection_box.color.a = a.u.i;

    toml_value_t piece_selection_width =
        toml_table_double(piece_selection, "width");
    if (!piece_selection_width.ok) {
        return 1;
    }
    conf->piece_selection_box.width = piece_selection_width.u.d;

    toml_table_t *taken_piece_offsets =
        toml_table_table(tb, "taken_piece_offsets");

    toml_value_t taken_piece_offets_x =
        toml_table_double(taken_piece_offsets, "x");
    if (!taken_piece_offets_x.ok) {
        return 1;
    }
    conf->taken_piece_offsets.x_pc = taken_piece_offets_x.u.d;

    toml_value_t taken_piece_offets_y =
        toml_table_double(taken_piece_offsets, "y");
    if (!taken_piece_offets_y.ok) {
        return 1;
    }
    conf->taken_piece_offsets.y_pc = taken_piece_offets_y.u.d;

    toml_value_t taken_piece_offets_y_factor =
        toml_table_double(taken_piece_offsets, "y_factor");
    if (!taken_piece_offets_y_factor.ok) {
        return 1;
    }
    conf->taken_piece_offsets.y_pc_factor = taken_piece_offets_y_factor.u.d;

    toml_table_t *promotion = toml_table_table(tb, "promotion_selection");

    toml_value_t val = toml_table_double(promotion, "queen_x");
    if (!val.ok) {
        return 1;
    }
    conf->promotion_selection.queen.x = val.u.d;

    val = toml_table_double(promotion, "queen_y");
    if (!val.ok) {
        return 1;
    }
    conf->promotion_selection.queen.y = val.u.d;

    val = toml_table_double(promotion, "rook_x");
    if (!val.ok) {
        return 1;
    }
    conf->promotion_selection.rook.x = val.u.d;

    val = toml_table_double(promotion, "rook_y");
    if (!val.ok) {
        return 1;
    }
    conf->promotion_selection.rook.y = val.u.d;

    val = toml_table_double(promotion, "bishop_x");
    if (!val.ok) {
        return 1;
    }
    conf->promotion_selection.bishop.x = val.u.d;

    val = toml_table_double(promotion, "bishop_y");
    if (!val.ok) {
        return 1;
    }
    conf->promotion_selection.bishop.y = val.u.d;

    val = toml_table_double(promotion, "knight_x");
    if (!val.ok) {
        return 1;
    }
    conf->promotion_selection.knight.x = val.u.d;

    val = toml_table_double(promotion, "knight_y");
    if (!val.ok) {
        return 1;
    }
    conf->promotion_selection.knight.y = val.u.d;

    val = toml_table_double(promotion, "size");
    if (!val.ok) {
        return 1;
    }
    conf->promotion_selection.size = val.u.d;

    toml_free(tb);

    return 0;
}