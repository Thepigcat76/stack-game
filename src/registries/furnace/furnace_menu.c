#include "furnace_menu.h"
#include <stdlib.h>

void *tile_furnace_create_menu(TileInstance *tile, MenuContext context) {
    FurnaceMenu *menu = malloc(sizeof(FurnaceMenu));
    menu->instance = tile;
    menu->context = context;
    return menu;
}
