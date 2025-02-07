#pragma once

#include "data/data.h"
#include "raylib.h"
#include "stack.h"

#define LAYER_ELEMENTS_AMOUNT 16
#define DEFAULT_ELEMENT_SIZE 4

void create_elements();

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
} TileInstance;

typedef void (*ElementInitFunc)(const TileInstance *elem);
typedef void (*ElementTickFunc)(TileInstance *elem);

ElementType element_type_new_advanced(char *name,
                                      ElementInitFunc init_elem_func,
                                      ElementTickFunc tick_func);

ElementType element_type_new_simple(char *name);

bool element_type_cmp(ElementType type0, ElementType type1);

TileInstance element_new(ElementType type, Vector2 pos);

void element_draw(const TileInstance *elem);

typedef struct {
  TileInstance elements[LAYER_ELEMENTS_AMOUNT][LAYER_ELEMENTS_AMOUNT];
  Vector2 ticking_elements[LAYER_ELEMENTS_AMOUNT * LAYER_ELEMENTS_AMOUNT];
  Vector2 custom_data_elements[LAYER_ELEMENTS_AMOUNT * LAYER_ELEMENTS_AMOUNT];
} Layer;

Layer layer_generate();

void layer_draw(const Layer *layer);

DEFINE_STACK_EXPORTS(Layer);

typedef struct {
  STACK(Layer) layers;
} Game;