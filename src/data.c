#include "data.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

bool data_map_contains(const DataMap *data_map, char *key) {
  for (size_t i = 0; i < data_map->len; i++) {
    if (strcmp(key, data_map->keys[i]) == 0) {
      return true;
    }
  }
  return false;
}

Data data_map_get(const DataMap *data_map, char *key) {
    for (size_t i = 0; i < data_map->len; i++) {
        if (strcmp(key, data_map->keys[i]) == 0) {
            return data_map->values[i];
        }
    }
    fprintf(stderr, "Data Map does not contain key: %s\n", key);
    exit(EXIT_FAILURE);
}

void data_map_insert(DataMap *data_map, char *key, Data val) {
    data_map->keys[data_map->len] = key;
    data_map->values[data_map->len] = val;
    data_map->len++;
}
