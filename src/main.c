#include "conf.h"
#include "raylib.h"
#include "screens/button.h"
#include "screens/game_screen.h"
#include "state.h"
#include "win.h"
#include <stdio.h>

int main() {
    GameState state;
    reset_board(&state);

    state.scene = START_MENU;

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

        switch (state.scene) {
        case START_MENU:
            Button b = {.pos = (Vector2){.x = 10, .y = 10},
                        .size = (Vector2){.x = 100, .y = 50}};

            button_draw(&b, &state.conf);

            break;
        case GAME:
            draw_board(&state);
            break;
        case END_MENU:
            break;
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}