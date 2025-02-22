#pragma once

#include "../items/item.h"
#include "registry.h"

create_registry(ItemType)

extern Registry(ItemType) ITEMS;

extern ItemType ITEM_AIR;
extern ItemType ITEM_PICKAXE;

void init_items();
