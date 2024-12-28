#pragma once

#include "raylib.h"
#include "stack.h"

void create_elements();

typedef struct {
  char *name;
  Texture2D texture;
  float scale;
  bool has_texture;
} ElementType;

extern ElementType AIR;
extern ElementType STONE;
extern ElementType GRASS;
extern ElementType DIRT;

ElementType element_type_new(char *name, float scale);

bool element_type_cmp(ElementType type0, ElementType type1);

typedef struct {
  ElementType type;
  Rectangle box;
} Element;

Element element_new(ElementType type, Vector2 pos);

void element_draw(const Element *elem);

typedef struct {
  Element elements[16][16];
} Layer;

Layer layer_generate();

void layer_draw(const Layer *layer);

DEFINE_STACK_EXPORTS(Layer);

typedef struct {
  STACK(Layer) layers;
} Game;