#pragma once

#include "../data/data.h"
#include "raylib.h"

typedef struct {
  char *name;
  Texture2D texture;
  float scale;
  bool has_texture;
  bool is_solid;

  // Advanced
  bool is_ticking;
  bool stores_custom_data;
  bool has_menu;
  void *init_elem;
  void *tick;
  void *create_menu;
} TileType;

typedef struct _tile_instance {
  TileType type;
  Rectangle box;
  DataMap custom_data;
  void (*init_elem)(const struct _tile_instance *elem);
  void (*tick)(struct _tile_instance *elem);
  void *(*create_menu)(struct _tile_instance *elem);
} TileInstance;

typedef struct {
  Rectangle rect;
  char *menu_name;
} MenuContext;

typedef void (*TileInitFunc)(const TileInstance *tile);
typedef void (*TileTickFunc)(TileInstance *tile);
typedef void *(*TileCreateMenuFunc)(TileInstance *tile, MenuContext context);

TileInstance tile_new(TileType type, Vector2 pos);
