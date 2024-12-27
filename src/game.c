#include "game.h"
#include "string.h"
#include "mymath.h"

DEFINE_STACK(Layer);

Element ELEMENTS[3];

Element STONE;
Element GRASS;
Element DIRT;

void create_elements() {
  STONE = element_new("stone", 4);
  GRASS = element_new("grass", 4);
  DIRT = element_new("dirt", 4);
  ELEMENTS[0] = STONE;
  ELEMENTS[1] = GRASS;
  ELEMENTS[2] = DIRT;
}

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
      element_draw(&layer->elements[y][x],
                   vec2(x * 4 * 16, y * 4 * 16 + layer_y));
    }
  }
}