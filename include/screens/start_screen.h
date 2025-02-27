#pragma once

#include "screens/button.h"
#include "state.h"

typedef struct {
    Button start_button, exit_button;
} StartScreen;

StartScreen start_scene_init();

void start_screen_update(StartScreen *s, GameState *state);

void start_screen_render(const StartScreen *s, const GameState *state);