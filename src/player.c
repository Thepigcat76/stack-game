#include "player.h"
#include "mymath.h"
#include "utils.h"
#include <raylib.h>

const Direction DIRECTIONS[] = {RIGHT, LEFT, UP, DOWN};

Player player_new(char *asset_name, uint8_t scale) {
  Image img = load_image_asset(asset_name);
  uint32_t img_width = img.width;
  uint32_t img_height = img.height;
  Texture2D texture = LoadTextureFromImage(img);
  UnloadImage(img);

  Player player;
  player.texture = texture;
  player.scale = scale;
  player.box = (Rectangle){.x = 200,
                           .y = -200,
                           .width = img_width * player.scale,
                           .height = img_height * player.scale};
  player.window_open = false;

  return player;
}

Vector2 player_pos(Player *player) {
  return vec2(player->box.x, player->box.y);
}

void player_draw(Player *player) {
  DrawTextureEx(player->texture, player_pos(player), 0, player->scale, WHITE);
}

Rectangle rec_offset_direction(const Rectangle *rec, Direction direction,
                               int32_t distance) {
  switch (direction) {
  case RIGHT:
    return rec_offset(rec, distance, 0, 0, 0);
  case LEFT:
    return rec_offset(rec, -distance, 0, 0, 0);
  case UP:
    return rec_offset(rec, 0, -distance, 0, 0);
  case DOWN:
    return rec_offset(rec, 0, distance, 0, 0);
  }
}