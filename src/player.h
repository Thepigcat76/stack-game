#pragma once

#include "raylib.h"
#include <stdint.h>

typedef struct {
    Texture2D texture;
    Rectangle box;
    uint8_t scale;
} Player;

Player player_new(char *asset_name, uint8_t scale);

Vector2 player_pos(Player *player);

void player_draw(Player *player);
