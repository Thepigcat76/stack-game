#pragma once

#include <stdint.h>
#include <stdlib.h>

#define BYTE_SIZE 8

typedef struct {
  uint8_t *bytes;
  size_t writer_index;
  size_t reader_index;
  size_t capacity;
} ByteBuf;

void byte_buf_write_byte(ByteBuf *buf, uint8_t byte);

void byte_buf_write_int(ByteBuf *buf, int32_t integer);

void byte_buf_write_string(ByteBuf *buf, char *str);

uint8_t byte_buf_read_byte(ByteBuf *buf);

int32_t byte_buf_read_int(ByteBuf *buf);

void byte_buf_read_string(ByteBuf *buf, char *str_buf);

char *byte_buf_read_string_heap(ByteBuf *buf);

void byte_buf_to_bin(ByteBuf *buf, char *str_buf);

void byte_buf_from_bin(ByteBuf *buf, const char *str_buf);

#define byte_buf_write_list(buf, func, list, len)                              \
  byte_buf_write_int(buf, len);                                                \
  for (int i = 0; i < len; i++) {                                              \
    func(buf, list[i]);                                                        \
  }

#define byte_buf_read_list(buf, func, list)                                    \
  int32_t len = byte_buf_read_int(buf);                                        \
  for (int i = 0; i < len; i++) {                                              \
    list[i] = func(buf);                                                       \
  }

