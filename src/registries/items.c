#include "items.h"
#include "../utils.h"

Registry(ItemType) ITEMS;

ItemType ITEM_AIR;
ItemType ITEM_PICKAXE;

void init_items() {
    ITEM_AIR = (ItemType) {.name = "air", .texture = {0}, .has_texture = false};
    ITEM_PICKAXE = (ItemType) {.name = "pickaxe", .texture = load_texture("pickaxe"), .has_texture = true};
}
