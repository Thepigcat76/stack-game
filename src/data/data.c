#include "data.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
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

void byte_buf_write_data_map(ByteBuf *buf, const DataMap *map) {
  byte_buf_write_int(buf, map->len);
  for (int i = 0; i < map->len; i++) {
    byte_buf_write_string(buf, map->keys[i]);
    byte_buf_write_data(buf, map->values[i]);
  }
}

void byte_buf_read_data_map(ByteBuf *buf, DataMap *map) {
  size_t len = byte_buf_read_int(buf);

  for (int i = 0; i < len; i++) {
    data_map_insert(map, byte_buf_read_string_heap(buf),
                    byte_buf_read_data(buf));
  }
}

void byte_buf_write_data(ByteBuf *buf, Data data) {
  byte_buf_write_byte(buf, data.type);
  switch (data.type) {
  case DATA_TYPE_INT:
    byte_buf_write_int(buf, data.var.data_int);
    break;
  case DATA_TYPE_CHAR:
    byte_buf_write_byte(buf, data.var.data_char);
    break;
  case DATA_TYPE_STRING:
    byte_buf_write_string(buf, data.var.data_string);
    break;
  default:
    fprintf(stderr, "Error writing data");
  }
}

Data byte_buf_read_data(ByteBuf *buf) {
  uint8_t type = byte_buf_read_byte(buf);

  switch (type) {
  case DATA_TYPE_INT: {
    int32_t integer = byte_buf_read_int(buf);
    return (Data){.type = type, .var = {.data_int = integer}};
  }
  case DATA_TYPE_CHAR: {
    uint8_t character = byte_buf_read_byte(buf);
    return (Data){.type = type, .var = {.data_char = character}};
  }
  case DATA_TYPE_STRING: {
    char *string = byte_buf_read_string_heap(buf);
    return (Data){.type = type, .var = {.data_string = string}};
  }
  default:
    fprintf(stderr, "Error reading data");
  }
}
