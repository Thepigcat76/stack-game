#include "game.h"
#include "mymath.h"
#include "utils.h"
#include <raylib.h>
#include <stdio.h>
#include <string.h>

#define ELEMENTS_AMOUNT 5

DEFINE_STACK(Layer);

ElementType ELEMENTS[ELEMENTS_AMOUNT];

ElementType AIR;
ElementType STONE;
ElementType GRASS;
ElementType DIRT;
ElementType FURNACE;

static ElementType element_type_new_air();

void elem_furnace_init(const struct _element *elem) {
  printf("test\n");
}

void elem_furnace_tick(Element *elem) {

}

void create_elements() {
  AIR = element_type_new_air();
  STONE = element_type_new_simple("stone");
  GRASS = element_type_new_simple("grass");
  DIRT = element_type_new_simple("dirt");
  FURNACE = element_type_new_advanced("furnace", elem_furnace_init, elem_furnace_tick);
  ELEMENTS[0] = STONE;
  ELEMENTS[1] = GRASS;
  ELEMENTS[2] = DIRT;
  ELEMENTS[3] = AIR;
  ELEMENTS[4] = FURNACE;
}

ElementType element_type_new_simple(char *name) {
  return (ElementType){
      .name = name,
      .texture = load_texture(name),
      .scale = DEFAULT_ELEMENT_SIZE,
      .has_texture = true,
      .is_solid = true,
      .is_ticking = false,
      .stores_custom_data = false,
      .init_elem = NULL,
      .tick = NULL,
  };
}

ElementType element_type_new_advanced(char *name,
                                      ElementInitFunc init_elem_func,
                                      ElementTickFunc tick_func) {
  return (ElementType){
      .name = name,
      .texture = load_texture(name),
      .scale = DEFAULT_ELEMENT_SIZE,
      .has_texture = true,
      .is_solid = true,
      .is_ticking = true,
      .stores_custom_data = true,
      .init_elem = init_elem_func,
      .tick = tick_func,
  };
}

static ElementType element_type_new_air() {
  return (ElementType){
      .name = "air",
      .scale = 0,
      .has_texture = false,
      .texture = {.width = 0, .height = 0},
      .is_solid = false,
      .is_ticking = false,
      .stores_custom_data = false,
  };
}

Element element_new(ElementType type, Vector2 pos) {
  Element elem;
  elem.type = type;
  elem.box = (Rectangle){.x = pos.x,
                         .y = pos.y,
                         .width = type.texture.width * type.scale,
                         .height = type.texture.height * type.scale};
  elem.init_elem = (ElementInitFunc) type.init_elem;
  elem.tick = (ElementTickFunc) type.tick;
  return elem;
}

bool element_type_cmp(ElementType type0, ElementType type1) {
  return strcmp(type0.name, type1.name) == 0;
}

void element_draw(const Element *elem) {
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
      ElementType elem_type = ELEMENTS[rand];

      while (!element_type_cmp(elem_type, AIR) && rand != 0) {
        rand = random_number(0, 3);
        elem_type = ELEMENTS[rand];
      }

      if (y > 0) {
        Element above_elem = layer.elements[y - 1][x];
        if (element_type_cmp(above_elem.type, GRASS)) {
          elem_type = DIRT;
        } else if (!element_type_cmp(above_elem.type, AIR) &&
                   element_type_cmp(elem_type, GRASS)) {
          int32_t rand = 0;
          while (element_type_cmp(elem_type, GRASS)) {
            rand = random_number(0, 3);
            elem_type = ELEMENTS[rand];
          }
        } else if (element_type_cmp(above_elem.type, AIR)) {
          elem_type = GRASS;
        }
      }

      Element elem = element_new(
          elem_type, vec2(x * elem_type.texture.width * elem_type.scale,
                          y * elem_type.texture.height * elem_type.scale));
      layer.elements[y][x] = elem;
    }
  }
  return layer;
}

void layer_draw(const Layer *layer) {
  for (int32_t y = 0; y < 16; y++) {
    for (int32_t x = 0; x < 16; x++) {
      element_draw(&layer->elements[y][x]);
    }
  }
}
