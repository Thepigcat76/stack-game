#pragma once

#include <raylib.h>
#include <stdint.h>

Image load_image_asset(char *name);

Rectangle rec_offset(const Rectangle *rectangle, int32_t x_offset,
                               int32_t y_offset, int32_t width_offset,
                               int32_t height_offset);

Texture2D load_texture(char *name);
