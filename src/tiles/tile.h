#pragma once

#include "raylib.h"
#include "../data.h"

typedef struct {
  char *name;
  Texture2D texture;
  float scale;
  bool has_texture;
  bool is_solid;

  // Advanced
  bool is_ticking;
  bool stores_custom_data;
  void *init_elem;
  void *tick;
} ElementType;

extern ElementType AIR;
extern ElementType STONE;
extern ElementType GRASS;
extern ElementType DIRT;
extern ElementType FURNACE;

typedef struct _element {
  ElementType type;
  Rectangle box;
  DataMap custom_data;
  void (*init_elem)(const struct _element *elem);
  void (*tick)(struct _element *elem);
} Element;

typedef void (*ElementInitFunc)(const Element *elem);
typedef void (*ElementTickFunc)(Element *elem);