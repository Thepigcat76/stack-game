#include "../tiles/tile.h"

#define TILES_AMOUNT 5

#define DEFAULT_TILE_SIZE 4

extern TileType TILES[TILES_AMOUNT];

extern TileType AIR;
extern TileType STONE;
extern TileType GRASS;
extern TileType DIRT;
extern TileType FURNACE;

void create_tiles();
