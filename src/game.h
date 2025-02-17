#pragma once

#include "data/data.h"
#include "tiles/tile.h"
#include "raylib.h"
#include "stack.h"

#define LAYER_TILES_AMOUNT 16

TileType element_type_new_advanced(char *name,
                                      ElementInitFunc init_elem_func,
                                      ElementTickFunc tick_func);

TileType element_type_new_simple(char *name);

bool element_type_cmp(TileType type0, TileType type1);

void element_draw(const TileInstance *elem);

typedef struct {
  TileInstance tiles[LAYER_TILES_AMOUNT][LAYER_TILES_AMOUNT];
  Vector2 ticking_elements[LAYER_TILES_AMOUNT * LAYER_TILES_AMOUNT];
  Vector2 custom_data_elements[LAYER_TILES_AMOUNT * LAYER_TILES_AMOUNT];
} Layer;

Layer layer_generate();

void layer_draw(const Layer *layer);

DEFINE_STACK_EXPORTS(Layer);

typedef struct {
  STACK(Layer) layers;
} Game;