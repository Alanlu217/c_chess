#include "screens/start_screen.h"
#include "raylib.h"
#include "screens/button.h"
#include "state.h"

void start_scene_init(GameState *state) {
    state->start_screen.start_button =
        (Button){.pos = (Vector2){.x = 0.5, .y = 0.45},
                 .size = (Vector2){.x = 0.5, .y = 0.06},
                 .text = "Start"};

    state->start_screen.exit_button =
        (Button){.pos = (Vector2){.x = 0.5, .y = 0.55},
                 .size = (Vector2){.x = 0.5, .y = 0.06},
                 .text = "Exit"};
}

void start_screen_update(GameState *state) {
    if (button_pressed(&state->start_screen.start_button, state)) {
        state->scene = GAME;
    }

    if (button_pressed(&state->start_screen.exit_button, state)) {
        state->running = false;
    }
}

void start_screen_render(const GameState *state) {
    button_draw(&state->start_screen.start_button, state);
    button_draw(&state->start_screen.exit_button, state);
}