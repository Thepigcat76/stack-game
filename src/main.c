#include "raylib.h"
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "mymath.h"

int main() {
  srand(time(0));
  // Initialize the window
  const int screen_width = 800;
  const int screen_height = 600;
  InitWindow(screen_width, screen_height, "Basic Raylib Program");

  create_elements();

  Layer layer = layer_generate();

  Image playerImage = LoadImage("assets/player.png");
  Texture2D texture = LoadTextureFromImage(playerImage);
  UnloadImage(playerImage);

  // Define circle properties
  Vector2 player_position = {screen_width / 2.0f, screen_height / 2.0f};
  float speed = 5.0f;

  // Set the target FPS

  Camera2D camera = {0};
  camera.target =
      (Vector2){screen_width / 2.0f, screen_height / 2.0f}; // Center
  camera.offset = (Vector2){screen_width / 2.0f,
                            screen_height / 2.0f}; // Offset from center
  camera.rotation = 0.0f; // No rotation initially
  camera.zoom = 1.0f;     // Default zoom level
  SetTargetFPS(60);

  // Main game loop
  while (!WindowShouldClose()) {           // Check if the window should close
    // Update
    if (IsKeyDown(KEY_UP)){
      camera.target.y -= 5;
      player_position.y -= 5;
      }

    // Draw
    BeginDrawing();
    ClearBackground(RAYWHITE); // End 3D mode
    BeginMode2D(camera);       // Start 2D mode

    element_draw(&GRASS, vec2(200, 0));
    element_draw(&DIRT, vec2(200, 200));
    element_draw(&STONE, vec2(200, 400));
    layer_draw(&layer);
    DrawTextureEx(texture, player_position, 0, 4, WHITE);
    EndMode2D(); // End 2D mode
    EndDrawing();
  }

  // De-initialize the window
  CloseWindow();

  return 0;
}
