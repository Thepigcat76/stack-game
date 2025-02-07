#pragma once

#include "raylib.h"
#include "../data/data.h"

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
} TileType;

extern TileType AIR;
extern TileType STONE;
extern TileType GRASS;
extern TileType DIRT;
extern TileType FURNACE;

typedef struct _element {
  TileType type;
  Rectangle box;
  DataMap custom_data;
  void (*init_elem)(const struct _element *elem);
  void (*tick)(struct _element *elem);
} TileInstance;

typedef void (*ElementInitFunc)(const TileInstance *elem);
typedef void (*ElementTickFunc)(TileInstance *elem);