#include "mymath.h"
#include <stdint.h>
#include <stdlib.h>
#include <raylib.h>

int32_t random_number(int32_t min, int32_t max) { return rand() % (max + 1) + min; }

Vector2 vec2(float x, float y) { return (Vector2){x, y}; }