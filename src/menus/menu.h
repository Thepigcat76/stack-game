#pragma once

#include "../game.h"
#include <stdint.h>
#include <raylib.h>
#include <stdint.h>

#define DEFAULT_WINDOW_SCALE 4
#define DEFAULT_WINDOW_WIDTH 96 * DEFAULT_WINDOW_SCALE
#define DEFAULT_WINDOW_HEIGHT 80 * DEFAULT_WINDOW_SCALE

typedef struct {
  enum {
    MENU_FURNACE,
  } type;
  union {

  } var;
} Menu;
