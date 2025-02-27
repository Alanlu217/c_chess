#include "screens/start_screen.h"
#include "raylib.h"
#include "screens/button.h"
#include "state.h"

StartScreen start_scene_init() {
    return (StartScreen){
        .start_button = (Button){.pos = (Vector2){.x = 0.5, .y = 0.45},
                                 .size = (Vector2){.x = 0.5, .y = 0.06},
                                 .text = "Start"},
        .exit_button = (Button){.pos = (Vector2){.x = 0.5, .y = 0.55},
                                .size = (Vector2){.x = 0.5, .y = 0.06},
                                .text = "Exit"}};
}

void start_screen_update(StartScreen *s, GameState *state) {
    if (button_pressed(&s->start_button, state)) {
        state->scene = GAME;
    }

    if (button_pressed(&s->exit_button, state)) {
        state->running = false;
    }
}

void start_screen_render(const StartScreen *s, const GameState *state) {
    button_draw(&s->start_button, state);
    button_draw(&s->exit_button, state);
}