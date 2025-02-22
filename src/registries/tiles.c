
#include "tiles.h"
#include "../utils.h"
#include "furnace/furnace_tile.h"
#include "furnace/furnace_menu.h"
#include "registry.h"
#include <stdio.h>

Registry(TileType) TILES;

static TileType tile_type_new_air();

TileType tile_type_new_simple(char *name);

TileType tile_type_new_advanced(char *name, TileInitFunc init_elem_func,
                                TileTickFunc tick_func, TileCreateMenuFunc tile_create_menu_func);

void init_tiles() {
  registry_init(TileType, TILES);

  TILE_AIR = tile_type_new_air();
  TILE_STONE = tile_type_new_simple("stone");
  TILE_GRASS = tile_type_new_simple("grass");
  TILE_DIRT = tile_type_new_simple("dirt");
  TILE_FURNACE =
      tile_type_new_advanced("furnace", tile_furnace_init, tile_furnace_tick, tile_furnace_create_menu);
  registry_add(TILES, TILE_AIR);
  registry_add(TILES, TILE_STONE);
  registry_add(TILES, TILE_GRASS);
  registry_add(TILES, TILE_DIRT);
  registry_add(TILES, TILE_FURNACE);
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

TileType tile_type_new_advanced(char *name, TileInitFunc init_elem_func,
                                TileTickFunc tick_func, TileCreateMenuFunc tile_create_menu_func) {
  return (TileType){
      .name = name,
      .texture = load_texture(name),
      .scale = DEFAULT_TILE_SIZE,
      .has_texture = true,
      .is_solid = true,
      .is_ticking = tick_func != NULL,
      .has_menu = tile_create_menu_func != NULL,
      .stores_custom_data = true,
      .init_elem = init_elem_func,
      .tick = tick_func,
      .create_menu = tile_create_menu_func,
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