#pragma once

#include "../../menus/menu.h"

typedef struct {
  MenuContext context;
  TileInstance *instance;
} FurnaceMenu;

void *tile_furnace_create_menu(TileInstance *tile, MenuContext context);