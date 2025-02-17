
#include "tiles.h"
#include <stdio.h>
#include "../utils.h"

TileType TILES[TILES_AMOUNT];

TileType AIR;
TileType STONE;
TileType GRASS;
TileType DIRT;
TileType FURNACE;

static TileType tile_type_new_air();

TileType tile_type_new_simple(char *name);

TileType tile_type_new_advanced(char *name, ElementInitFunc init_elem_func,
                                ElementTickFunc tick_func);

static void elem_furnace_init(const TileInstance *elem);

static void elem_furnace_tick(TileInstance *elem);

void create_tiles() {
  AIR = tile_type_new_air();
  STONE = tile_type_new_simple("stone");
  GRASS = tile_type_new_simple("grass");
  DIRT = tile_type_new_simple("dirt");
  FURNACE =
      tile_type_new_advanced("furnace", elem_furnace_init, elem_furnace_tick);
  TILES[0] = STONE;
  TILES[1] = GRASS;
  TILES[2] = DIRT;
  TILES[3] = AIR;
  TILES[4] = FURNACE;
}

TileType tile_type_new_simple(char *name) {
  return (TileType){
      .name = name,
      .texture = load_texture(name),
      .scale = DEFAULT_TILE_SIZE,
      .has_texture = true,
      .is_solid = true,
      .is_ticking = false,
      .stores_custom_data = false,
      .init_elem = NULL,
      .tick = NULL,
  };
}

TileType tile_type_new_advanced(char *name, ElementInitFunc init_elem_func,
                                ElementTickFunc tick_func) {
  return (TileType){
      .name = name,
      .texture = load_texture(name),
      .scale = DEFAULT_TILE_SIZE,
      .has_texture = true,
      .is_solid = true,
      .is_ticking = true,
      .stores_custom_data = true,
      .init_elem = init_elem_func,
      .tick = tick_func,
  };
}

static TileType tile_type_new_air() {
  return (TileType){
      .name = "air",
      .scale = 0,
      .has_texture = false,
      .texture = {.width = 0, .height = 0},
      .is_solid = false,
      .is_ticking = false,
      .stores_custom_data = false,
  };
}

static void elem_furnace_init(const TileInstance *elem) {
  printf("test\n");
}

static void elem_furnace_tick(TileInstance *elem) {
  printf("Ticking funcace\n");
}