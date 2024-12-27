#include "raylib.h"
#include "stack.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
  char *name;
  Texture2D texture;
  float scale;
} Element;

typedef struct {
  Element elements[16][16];
} Layer;

DEFINE_STACK_EXPORTS(Layer)
DEFINE_STACK(Layer)

typedef struct {
  STACK(Layer) layers;
} Game;

Element element_new(char *name, float scale) {
  Element elem;
  char path[strlen(name) + sizeof("assets/.png")];
  sprintf(path, "assets/%s.png", name);
  Image image = LoadImage(path);
  Texture2D texture = LoadTextureFromImage(image);
  UnloadImage(image);

  elem.name = name;
  elem.texture = texture;
  elem.scale = scale;

  return elem;
}

void element_draw(const Element *elem, Vector2 pos) {
  DrawTextureEx(elem->texture, pos, 0, elem->scale, WHITE);
}

Element ELEMENTS[3];

Element STONE;
Element GRASS;
Element DIRT;

int32_t random_number(int32_t min, int32_t max) { return rand() % max + min; }

Vector2 vec2(float x, float y) { return (Vector2){x, y}; }

Layer layer_generate() {
  Layer layer;
  for (int32_t y = 0; y < 16; y++) {
    for (int32_t x = 0; x < 16; x++) {
      int32_t rand = random_number(0, 3);
      Element elem = ELEMENTS[rand];
      layer.elements[y][x] = elem;
    }
  }
  return layer;
}

int32_t layer_y = 0;

void layer_draw(Layer *layer) {
  for (int32_t y = 0; y < 16; y++) {
    for (int32_t x = 0; x < 16; x++) {
      element_draw(&layer->elements[y][x], vec2(x * 4 * 16, y * 4 * 16 + layer_y));
    }
  }
}

void create_elements() {
  STONE = element_new("stone", 4);
  GRASS = element_new("grass", 4);
  DIRT = element_new("dirt", 4);
  ELEMENTS[0] = STONE;
  ELEMENTS[1] = GRASS;
  ELEMENTS[2] = DIRT;
}

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
