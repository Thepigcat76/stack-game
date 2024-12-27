#pragma once

#include "raylib.h"
#include "stack.h"

void create_elements();

typedef struct {
  char *name;
  Texture2D texture;
  float scale;
} Element;

extern Element STONE;
extern Element GRASS;
extern Element DIRT;

Element element_new(char *name, float scale);

void element_draw(const Element *elem, Vector2 pos);

typedef struct {
  Element elements[16][16];
} Layer;

Layer layer_generate();

void layer_draw(Layer *layer);

DEFINE_STACK_EXPORTS(Layer);

typedef struct {
  STACK(Layer) layers;
} Game;