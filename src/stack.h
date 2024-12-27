#pragma once

#include <stdlib.h>
#include <stdio.h>

#define STACK(type) stack_##type##_t

#define stack_new(type, size) stack_##type##_new(size)

#define stack_push(type, stack, value) stack_##type##_push(stack, value)

#define stack_pop(type, stack) stack_##type##_pop(stack)

#define stack_free(type, stack) stack_##type##_free(stack)

// clang-format off
#define DEFINE_STACK_EXPORTS(type)                                             \
  typedef struct {                                                             \
    type typehint;                                                             \
    type *data;                                                                \
    size_t length;                                                                \
    size_t capacity;                                                           \
  } STACK(type);                                                                            \
  \
  STACK(type) stack_##type##_new(size_t capacity);\
  void stack_##type##_push(STACK(type) *stack, type value);\
  type stack_##type##_pop(STACK(type) *stack);\
  void stack_##type##_free(STACK(type) *stack);\

#define DEFINE_STACK(type)                                                                               \
  STACK(type) stack_##type##_new(size_t capacity) {                                           \
    /**/                                                                       \
    STACK(type) stack;          \
    stack.data = (type *)malloc(sizeof(type) * capacity);                                 \
    stack.capacity = capacity;                                                         \
    stack.length = 0;                                                           \
    return stack;                                                                \
  }                                                                            \
                                                                               \
  static void stack_##type##_resize(STACK(type) *stack, size_t capacity) {        \
    type *items = (type *)realloc(stack->data, sizeof(type) * capacity);        \
    if (items) {                                                               \
      stack->data = items;                                                       \
      stack->capacity = capacity;                                                \
    }                                                                          \
  }                                                                            \
                                                                               \
  /* Function to free the memory used by the stack */                         \
  void stack_##type##_free(STACK(type) *stack) {                                 \
    free(stack->data);                                                           \
  }                                                                            \
                                                                               \
  /* Function to add an item to the stack */                                  \
  void stack_##type##_push(STACK(type) *stack, type value) {                 \
    if (stack->length == stack->capacity) {                                        \
      stack_##type##_resize(stack, stack->capacity * 2);                             \
    }                                                                          \
    stack->data[stack->length++] = value;                                           \
  }                                                                            \
                                                                               \
  type stack_##type##_pop(STACK(type) *stack) {                                   \
    size_t index = stack->length - 1;\
    if (index >= stack->length) {                                                \
      fprintf(stderr, "Index out of bounds\n");                                \
    }                                                                          \
                                                                               \
    type popped_element = stack->data[index];                                    \
                                                                               \
    for (size_t i = index; i < stack->length - 1; ++i) {                         \
      stack->data[i] = stack->data[i + 1];                                         \
    }                                                                          \
                                                                               \
    stack->length--;                                                             \
                                                                               \
    if (stack->length < stack->capacity / 2) {                                     \
      stack->capacity /= 2;                                                      \
      stack->data = (type *)realloc(stack->data, stack->capacity * sizeof(type));   \
      if (stack->data == NULL) {                                                 \
        fprintf(stderr, "Memory reallocation failed\n");                       \
        exit(EXIT_FAILURE);                                                    \
      }                                                                        \
    }                                                                          \
                                                                               \
    return popped_element;                                                     \
  }