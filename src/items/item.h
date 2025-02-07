#pragma once
#include <raylib.h>
#include <stdint.h>

typedef struct {
  char *name;
  Texture2D texture;
} ItemType;

typedef struct {
  ItemType item;
  uint32_t count;
} ItemInstance;
