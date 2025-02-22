#include "../tiles/tile.h"
#include "registry.h"

#define DEFAULT_TILE_SIZE 4

create_registry(TileType)

extern Registry(TileType) TILES;

extern TileType TILE_AIR;
extern TileType TILE_STONE;
extern TileType TILE_GRASS;
extern TileType TILE_DIRT;
extern TileType TILE_FURNACE;

void init_tiles();
