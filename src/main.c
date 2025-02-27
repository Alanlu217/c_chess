#include "conf.h"
#include "raylib.h"
#include "screens/button.h"
#include "screens/game_screen.h"
#include "state.h"
#include "win.h"

int main() {
    GameState state;
    reset_board(&state);

    state.scene = START_MENU;

    state.window_x = 1000;
    state.window_y = 1000;

    if (conf_load(&state.conf) != 0) {
        return 1;
    }

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(state.window_x, state.window_y, "chess");
    SetExitKey(KEY_NULL);

    load_textures(&state);

    update_window_state(&state);

    Button b = {.text = "Start!",
                .pos = (Vector2){.x = 0.5, .y = 0.5},
                .size = (Vector2){.x = 0.3, .y = 0.05}};

    while (!WindowShouldClose()) {
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
            button_draw(&b, &state);

            if (button_pressed(&b, &state)) {
                state.scene = GAME;
            }
            break;
        case GAME:
            draw_board(&state);

            if (IsKeyPressed(KEY_R)) {
                state.white_to_move = !state.white_to_move;
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