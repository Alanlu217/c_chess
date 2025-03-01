#include "conf.h"
#include "raylib.h"
#include "screens/game_screen.h"
#include "screens/start_screen.h"
#include "state.h"
#include "utarray.h"
#include "win.h"

int main() {
    GameState state;
    game_screen_init(&state);
    start_scene_init(&state);

    state.running = true;
    state.scene = START_MENU;

    state.window_x = 1000;
    state.window_y = 1000;

    state.game.valid_moves_icd =
        (UT_icd){sizeof(PieceLocation), NULL, NULL, NULL};
    state.game.selected_piece_valid_moves = NULL;
    utarray_new(state.game.selected_piece_valid_moves,
                &state.game.valid_moves_icd);

    if (conf_load(&state.conf) != 0) {
        return 1;
    }

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(state.window_x, state.window_y, "chess");
    SetExitKey(KEY_NULL);

    load_textures(&state);

    update_window_state(&state);

    while (state.running) {
        if (WindowShouldClose()) {
            state.running = false;
        }

        if (IsKeyPressed(KEY_BACKSLASH)) {
            if (conf_load(&state.conf) != 0) {
                CloseWindow();
                return 1;
            }
            TraceLog(LOG_INFO, "Updated config");
        }

        update_window_state(&state);

        BeginDrawing();
        ClearBackground(BLACK);

        switch (state.scene) {
        case START_MENU:
            start_screen_update(&state);

            start_screen_render(&state);
            break;
        case GAME:
            game_screen_update(&state);
            game_screen_render(&state);

            if (IsKeyPressed(KEY_R)) {
                state.game.view_as_white = !state.game.view_as_white;
            }
            break;
        case END_MENU:
            break;
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}