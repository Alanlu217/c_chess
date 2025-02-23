#include <stdio.h>

#include "raylib.h"

int main() {
  printf("Hi!\n");

  InitWindow(800, 600, "Test");

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}