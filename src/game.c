#include "game.h"
#include "mymath.h"
#include <raylib.h>
#include <string.h>
#include "registries/tiles.h"

DEFINE_STACK(Layer);

static TileType tile_type_new_air();

bool tile_type_cmp(TileType type0, TileType type1) {
  return strcmp(type0.name, type1.name) == 0;
}

void tile_draw(const TileInstance *elem) {
  if (elem->type.has_texture) {
    DrawTextureEx(elem->type.texture, vec2(elem->box.x, elem->box.y), 0,
                  elem->type.scale, WHITE);
  }
}

Layer layer_generate() {
  Layer layer;
  for (uint32_t y = 0; y < 16; y++) {
    for (uint32_t x = 0; x < 16; x++) {
      int32_t rand = random_number(0, 3);
      TileType elem_type = TILES[rand];

      while (!tile_type_cmp(elem_type, AIR) && rand != 0) {
        rand = random_number(0, 3);
        elem_type = TILES[rand];
      }

      if (y > 0) {
        TileInstance above_elem = layer.tiles[y - 1][x];
        if (tile_type_cmp(above_elem.type, GRASS)) {
          elem_type = DIRT;
        } else if (!tile_type_cmp(above_elem.type, AIR) &&
                   tile_type_cmp(elem_type, GRASS)) {
          int32_t rand = 0;
          while (tile_type_cmp(elem_type, GRASS)) {
            rand = random_number(0, 3);
            elem_type = TILES[rand];
          }
        } else if (tile_type_cmp(above_elem.type, AIR)) {
          elem_type = GRASS;
        }
      }

      TileInstance elem = tile_new(
          elem_type, vec2(x * elem_type.texture.width * elem_type.scale,
                          y * elem_type.texture.height * elem_type.scale));
      layer.tiles[y][x] = elem;
    }
  }
  return layer;
}

void layer_draw(const Layer *layer) {
  for (int32_t y = 0; y < 16; y++) {
    for (int32_t x = 0; x < 16; x++) {
      tile_draw(&layer->tiles[y][x]);
    }
  }
}
