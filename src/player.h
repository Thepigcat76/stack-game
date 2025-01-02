#pragma once

#include "gui.h"
#include "raylib.h"
#include <stdint.h>

typedef enum {
    RIGHT,
    LEFT,
    UP,
    DOWN,
} Direction;

extern const Direction DIRECTIONS[];

Rectangle rec_offset_direction(const Rectangle *rec, Direction direction,
                               int32_t distance);

typedef struct {
    Texture2D texture;
    Rectangle box;
    uint8_t scale;
    bool collissions[4];
    ElementWindow current_window;
    bool window_open;
} Player;

Player player_new(char *asset_name, uint8_t scale);

Vector2 player_pos(Player *player);

void player_draw(Player *player);
