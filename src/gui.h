#pragma once

#include "game.h"
#include <raylib.h>
#include <stdint.h>

#define DEFAULT_WINDOW_SCALE 4
#define DEFAULT_WINDOW_WIDTH 96 * DEFAULT_WINDOW_SCALE
#define DEFAULT_WINDOW_HEIGHT 80 * DEFAULT_WINDOW_SCALE

typedef struct {
  Vector2 pos;
  uint32_t width;
  uint32_t height;
  uint32_t scale;
  TileInstance *element;
} ElementWindowInfo;

typedef struct {
  Texture2D background;
  ElementWindowInfo window_info;
} FurnaceWindow;

typedef struct {
  enum {
    WINDOW_FURNACE,
  } type;
  union {
    FurnaceWindow furnace;
  } var;
} ElementWindow;

ElementWindowInfo element_window_info_new(Vector2 pos, uint32_t width,
                                          uint32_t height, uint32_t scale,
                                          TileInstance *element);

ElementWindowInfo element_window_info_new_simple(TileInstance *element);

void element_window_tick(ElementWindow *window);

void element_window_draw(const ElementWindow *window);

FurnaceWindow furnace_window_new(TileInstance *element);