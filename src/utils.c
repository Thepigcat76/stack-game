#include "utils.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

Image load_image_asset(char *name) {
  char path[strlen(name) + sizeof("assets/.png")];
  sprintf(path, "assets/%s.png", name);
  Image image = LoadImage(path);
  return image;
}

Rectangle rec_offset(const Rectangle *rectangle, int32_t x_offset,
                               int32_t y_offset, int32_t width_offset,
                               int32_t height_offset) {
  return (Rectangle){
      .x = rectangle->x + x_offset,
      .y = rectangle->y + y_offset,
      .width = rectangle->width + width_offset,
      .height = rectangle->height + height_offset,
  };
}

Texture2D load_texture(char *name) {
  Image image = load_image_asset(name);
  Texture2D texture = LoadTextureFromImage(image);
  UnloadImage(image);
  return texture;
}