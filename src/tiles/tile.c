#include "tile.h"

TileInstance tile_new(TileType type, Vector2 pos) {
  TileInstance elem;
  elem.type = type;
  elem.box = (Rectangle){.x = pos.x,
                         .y = pos.y,
                         .width = type.texture.width * type.scale,
                         .height = type.texture.height * type.scale};
  elem.init_elem = (ElementInitFunc)type.init_elem;
  elem.tick = (ElementTickFunc)type.tick;
  return elem;
}