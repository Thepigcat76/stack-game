#include "game.h"
#include "gui.h"
#include "mymath.h"
#include "player.h"
#include "raylib.h"
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

void camera_setup(Camera2D *camera, uint32_t screen_width,
                  uint32_t screen_height) {
  camera->target = (Vector2){screen_width / 2.0f, screen_height / 2.0f - 400};
  camera->offset = (Vector2){screen_width / 2.0f, screen_height / 2.0f};
  camera->rotation = 0.0f;
  camera->zoom = 1.0f;
}

void rec_draw_outline(const Rectangle *rec, Color color) {
  DrawRectangleLinesEx(*rec, 6, color);
}

void rec_draw(const Rectangle *rec, Color color) {
  DrawRectangle(rec->x, rec->y, rec->width, rec->height, color);
}

int main() {
  srand(time(0));
  const int screen_width = 800;
  const int screen_height = 600;
  InitWindow(screen_width, screen_height, "Basic Raylib Program");
  SetExitKey(0);

  create_elements();

  Layer layer = layer_generate();
  layer.elements[0][0] = element_new(FURNACE, vec2(0, 0));
  Player player = player_new("player", 4);

  float speed = 5.0f;

  Camera2D camera = {0};
  camera_setup(&camera, screen_width, screen_height);

  SetTargetFPS(60);

  const struct _element elem = layer.elements[0][0];
  elem.init_elem(&elem);

  while (!WindowShouldClose()) {
    for (size_t i = 0; i < 4; i++) {
      Element elem = layer.elements[0][0];
      player.collissions[i] =
          elem.type.is_solid
              ? CheckCollisionRecs(rec_offset_direction(&player.box, i, speed),
                                   elem.box)
              : false;
    }

    if (IsKeyDown(KEY_UP)) {
      if (!player.collissions[UP]) {
        camera.target.y -= speed;
        player.box.y -= speed;
      }
    }

    if (IsKeyDown(KEY_DOWN)) {
      if (!player.collissions[DOWN]) {
        camera.target.y += speed;
        player.box.y += speed;
      }
    }

    if (IsKeyDown(KEY_LEFT)) {
      if (!player.collissions[LEFT]) {
        camera.target.x -= speed;
        player.box.x -= speed;
      }
    }

    if (IsKeyDown(KEY_RIGHT)) {
      if (!player.collissions[RIGHT]) {
        camera.target.x += speed;
        player.box.x += speed;
      }
    }

    if (IsKeyDown(KEY_ESCAPE)) {
      player.window_open = false;
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode2D(camera);

    layer_draw(&layer);
    player_draw(&player);

    if (IsKeyDown(KEY_F3)) {
      Rectangle rec = player.box;
      rec_draw(&rec, BLUE);
      rec_draw(&layer.elements[0][0].box, GREEN);
    }

    Vector2 mouse_world_pos = GetScreenToWorld2D(GetMousePosition(), camera);
    Rectangle box = layer.elements[0][0].box;

    uint32_t x_index =
        (uint32_t)(mouse_world_pos.x / (16 * DEFAULT_ELEMENT_SIZE));
    uint32_t y_index =
        (uint32_t)(mouse_world_pos.y / (16 * DEFAULT_ELEMENT_SIZE));
    Rectangle rec = (Rectangle){.x = x_index * (16 * DEFAULT_ELEMENT_SIZE),
                                .y = y_index * (16 * DEFAULT_ELEMENT_SIZE),
                                .width = (16 * DEFAULT_ELEMENT_SIZE),
                                .height = (16 * DEFAULT_ELEMENT_SIZE)};
    rec_draw_outline(&rec, BLUE);

    if (CheckCollisionPointRec(mouse_world_pos, box)) {
      rec_draw_outline(&box, BLUE);
      if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        player.window_open = true;
        player.current_window =
            (ElementWindow){.type = WINDOW_FURNACE,
                            .var = furnace_window_new(&layer.elements[0][0])};
      }
    }
    
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && !(x_index == 0 && y_index == 0)) {
      layer.elements[y_index][x_index] =
          element_new(DIRT, vec2(x_index * (16 * DEFAULT_ELEMENT_SIZE),
                                 y_index * (16 * DEFAULT_ELEMENT_SIZE)));
    } else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      layer.elements[y_index][x_index] =
          element_new(AIR, vec2(x_index * (16 * DEFAULT_ELEMENT_SIZE),
                                 y_index * (16 * DEFAULT_ELEMENT_SIZE)));
    }

    EndMode2D();

    if (player.window_open) {
      element_window_draw(&player.current_window);
    }
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
