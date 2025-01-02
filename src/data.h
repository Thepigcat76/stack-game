#pragma once

#include <stdlib.h>

typedef struct {
  char **keys;
  struct _data *values;
  size_t len;
  size_t capacity;
} DataMap;

typedef struct {
  struct _data *items;
  size_t len;
} DataList;

typedef struct _data {
  enum {
    DATA_TYPE_MAP,
    DATA_TYPE_LIST,
    DATA_TYPE_SHORT,
    DATA_TYPE_INT,
    DATA_TYPE_LONG,
    DATA_TYPE_CHAR,
    DATA_TYPE_FLOAT,
    DATA_TYPE_DOUBLE,
  } type;
  union {
    DataMap data_map;
    DataList data_list;
    short data_short;
    int data_int;
    long data_long;
    char data_char;
    float data_float;
    double data_double;
  } var;
} Data;

Data data_map_get(const DataMap *data_map, char *key);

void data_map_insert(DataMap *data_map, char *key, Data val);
