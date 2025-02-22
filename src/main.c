#include "game.h"
#include "gui.h"
#include "mymath.h"
#include "player.h"
#include "raylib.h"
#include "registries/tiles.h"
#include "tiles/tile.h"
#include "data/bytebuf.h"
#include "data/data.h"
#include <registries/items.h>
#include <registries/registry.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void byte_buf_write_tile_type(ByteBuf *buf, const TileType *type) {
  byte_buf_write_string(buf, type->name);
}

TileType byte_buf_read_tile_type(ByteBuf *buf) {
  char *name = byte_buf_read_string_heap(buf);
  for (int i = 0; i < TILES.len; i++) {
    if (strcmp(name, registry_get(TILES, i).name) == 0) {
      return registry_get(TILES, i);
    }
  }
  fprintf(stderr, "Cannot read tile with name: %s\n", name);
  exit(1);
}

void byte_buf_write_rectangle(ByteBuf *buf, const Rectangle *rectangle) {
  byte_buf_write_int(buf, rectangle->x);
  byte_buf_write_int(buf, rectangle->y);
  byte_buf_write_int(buf, rectangle->width);
  byte_buf_write_int(buf, rectangle->height);
}

Rectangle byte_buf_read_rectangle(ByteBuf *buf) {
  Rectangle rect;
  rect.x = byte_buf_read_int(buf);
  rect.y = byte_buf_read_int(buf);
  rect.width = byte_buf_read_int(buf);
  rect.height = byte_buf_read_int(buf);
  return rect;
}

void byte_buf_write_tile_instance(ByteBuf *buf, const TileInstance *instance) {
  byte_buf_write_tile_type(buf, &instance->type);
  byte_buf_write_rectangle(buf, &instance->box);
  if (instance->type.stores_custom_data) {
    byte_buf_write_data(buf,
                        (Data){.type = DATA_TYPE_MAP,
                               .var = {.data_map = instance->custom_data}});
  }
}

TileInstance byte_buf_read_tile_instance(ByteBuf *buf) {
  TileInstance instance =
      tile_new(byte_buf_read_tile_type(buf), (Vector2){0, 0});
  instance.box = byte_buf_read_rectangle(buf);
  if (instance.type.stores_custom_data) {
    instance.custom_data = byte_buf_read_data(buf).var.data_map;
  }
  return instance;
}

void save_data(Layer *layer) {
  uint8_t bytes[4000];
  ByteBuf buf = {
      .bytes = bytes, .writer_index = 0, .reader_index = 0, .capacity = 4000};
  for (int i = 0; i < TILES.len; i++) {
    byte_buf_write_list(&buf, byte_buf_write_tile_instance, &layer->tiles[i],
                        TILES.len);
  }
}

int main() {
  srand(time(0));
  const int screen_width = 800;
  const int screen_height = 600;
  InitWindow(screen_width, screen_height, "Basic Raylib Program");
  SetExitKey(0);

  init_tiles();
  init_items();

  uint8_t read_bytes[4000];
  ByteBuf read_buf = {.bytes = read_bytes, .reader_index = 0, .writer_index = 0, .capacity = 4000};
  byte_buf_from_file(&read_buf);

  Layer layer = layer_generate();
  layer.tiles[0][0] = byte_buf_read_tile_instance(&read_buf);
  Player player = player_new("player", 4);

  float speed = 5.0f;

  Camera2D camera = {0};
  camera_setup(&camera, screen_width, screen_height);

  SetTargetFPS(60);

  //const TileInstance elem = layer.tiles[0][0];
  //elem.init_elem(&elem);

  while (!WindowShouldClose()) {
    /*for (size_t i = 0; i < 4; i++) {
      TileInstance elem = layer.tiles[0][0];
      player.collissions[i] =
          elem.type.is_solid
              ? CheckCollisionRecs(rec_offset_direction(&player.box, i, speed),
                                   elem.box)
              : false;
    }*/

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
      rec_draw(&layer.tiles[0][0].box, GREEN);
    }

    Vector2 mouse_world_pos = GetScreenToWorld2D(GetMousePosition(), camera);
    Rectangle box = layer.tiles[0][0].box;

    uint32_t x_index = (uint32_t)(mouse_world_pos.x / (16 * DEFAULT_TILE_SIZE));
    uint32_t y_index = (uint32_t)(mouse_world_pos.y / (16 * DEFAULT_TILE_SIZE));
    Rectangle rec = (Rectangle){.x = x_index * (16 * DEFAULT_TILE_SIZE),
                                .y = y_index * (16 * DEFAULT_TILE_SIZE),
                                .width = (16 * DEFAULT_TILE_SIZE),
                                .height = (16 * DEFAULT_TILE_SIZE)};
    rec_draw_outline(&rec, BLUE);

    if (CheckCollisionPointRec(mouse_world_pos, box)) {
      rec_draw_outline(&box, BLUE);
      if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        player.window_open = true;
        player.current_window =
            (ElementWindow){.type = WINDOW_FURNACE,
                            .var = furnace_window_new(&layer.tiles[0][0])};
      }
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) &&
        !(x_index == 0 && y_index == 0)) {
      layer.tiles[y_index][x_index] =
          tile_new(TILE_DIRT, vec2(x_index * (16 * DEFAULT_TILE_SIZE),
                              y_index * (16 * DEFAULT_TILE_SIZE)));
    } else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      layer.tiles[y_index][x_index] =
          tile_new(TILE_AIR, vec2(x_index * (16 * DEFAULT_TILE_SIZE),
                             y_index * (16 * DEFAULT_TILE_SIZE)));
    }

    EndMode2D();

    if (player.window_open) {
      element_window_draw(&player.current_window);
    }
    EndDrawing();
  }

  CloseWindow();

  uint8_t bytes[4000];
  ByteBuf buf = {.bytes = bytes, .writer_index = 0, .reader_index = 0, .capacity = 4000};
  byte_buf_write_tile_instance(&buf, &layer.tiles[0][0]);

  byte_buf_to_file(&buf);
}
