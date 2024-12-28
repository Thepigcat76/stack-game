#include "game.h"
#include "player.h"
#include "raylib.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void camera_setup(Camera2D *camera, uint32_t screen_width,
                  uint32_t screen_height) {
  camera->target = (Vector2){screen_width / 2.0f, screen_height / 2.0f - 400};
  camera->offset = (Vector2){screen_width / 2.0f, screen_height / 2.0f};
  camera->rotation = 0.0f;
  camera->zoom = 1.0f;
}

int main() {
  srand(time(0));
  const int screen_width = 800;
  const int screen_height = 600;
  InitWindow(screen_width, screen_height, "Basic Raylib Program");

  create_elements();

  Layer layer = layer_generate();
  Player player = player_new("player", 4);

  float speed = 5.0f;

  Camera2D camera = {0};
  camera_setup(&camera, screen_width, screen_height);

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    if (IsKeyDown(KEY_UP)) {
      camera.target.y -= 5;
      player.box.y -= 5;
    }

    if (IsKeyDown(KEY_DOWN)) {
      printf("%f, %f\n", player.box.x, player.box.y);
      if (!CheckCollisionRecs((Rectangle){.x = player.box.x,
                                          .y = player.box.y - 5,
                                          .width = player.box.width,
                                          .height = player.box.height},
                              layer.elements[0][0].box)) {
        camera.target.y += 5;
        player.box.y += 5;
      }
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode2D(camera);

    layer_draw(&layer);
    player_draw(&player);

    EndMode2D();
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
