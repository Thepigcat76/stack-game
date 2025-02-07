#pragma once

#include "raylib.h"

typedef struct {
  char *name;
  Texture2D texture;
} BeingType;

typedef struct {
  BeingType being;
  Vector2 pos;
} BeingInstance;
