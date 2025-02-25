#include "board_logic.h"
#include "conf.h"
#include "raylib.h"
#include "rendering.h"
#include "state.h"
#include "win.h"

int main() {
    GameState state;
    reset_board(&state);

    state.window_x = 1000;
    state.window_y = 1000;

    conf_load(&state.conf);

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(state.window_x, state.window_y, "chess");
    SetExitKey(KEY_NULL);

    load_textures(&state);

    update_window_state(&state);

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_BACKSLASH)) {
            conf_load(&state.conf);
            TraceLog(LOG_INFO, "Updated config");
        }

        update_window_state(&state);

        BeginDrawing();
        ClearBackground(BLACK);

        draw_board(&state);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}