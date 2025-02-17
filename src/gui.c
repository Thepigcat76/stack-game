#include "gui.h"
#include "mymath.h"
#include "utils.h"
#include "raylib.h"
#include "tiles/tile.h"

ElementWindowInfo element_window_info_new(Vector2 pos, uint32_t width,
                                          uint32_t height, uint32_t scale,
                                          TileInstance *element) {
  return (ElementWindowInfo){
      .pos = pos, .width = width, .height = height, .element = element};
}

ElementWindowInfo element_window_info_new_simple(TileInstance *element) {
  ElementWindowInfo info;
  info.width = DEFAULT_WINDOW_WIDTH;
  info.height = DEFAULT_WINDOW_HEIGHT;
  info.pos = vec2((GetScreenWidth() - info.width) / 2.0f,
                  (GetScreenHeight() - info.height) / 2.0f);
  info.scale = DEFAULT_WINDOW_SCALE;
  info.element = element;
  return info;
}

void furnace_window_draw(const FurnaceWindow *window) {
  DrawTextureEx(window->background, window->window_info.pos, 0,
                window->window_info.scale, WHITE);
}

void element_window_tick(ElementWindow *window);

void element_window_draw(const ElementWindow *window) {
  switch (window->type) {
  case WINDOW_FURNACE:
    furnace_window_draw(&window->var.furnace);
    break;
  }
}

FurnaceWindow furnace_window_new(TileInstance *element) {
  return (FurnaceWindow){
      .background = load_texture("furnace_gui"),
      .window_info = element_window_info_new_simple(element),
  };
}
