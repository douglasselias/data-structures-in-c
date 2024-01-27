#include "arena.c"
#include <string.h>

typedef struct {
  u64 size;
  u64 max_size;
  u8 *data;
} Array;

Array *create_array(Arena *arena, u64 max_size) {
  Array *array = alloc_arena(arena, sizeof(Array));
  array->size = 0;
  array->max_size = max_size;
  array->data = alloc_arena(arena, max_size);
  return array;
}

// void destroy_array() {}

void array_append(Arena *arena, Array *array, u8 value) {
  if (array->size + 1 <= array->max_size) {
    array->data[array->size] = value;
  } else {
    /// @note: resize the array
    // u8 *old_array_data = array->data;
    array->max_size *= 2;
    u8 *new_data = alloc_arena(arena, array->max_size);
    // array->data = alloc_arena(arena, array->max_size);
    for (u64 i = 0; i < array->size; i++) {
      new_data[i] = array->data[i];
    }
    new_data[array->size] = value;
    // free(array->data);
    array->data = new_data;
  }
  array->size++;
}

void array_remove_by_index(Array *array, u64 index) {
  u8 on_the_right = array->size - index - 1;
  u8 *dest = array->data + index;
  u8 *src = array->data + index + 1;
  memcpy(dest, src, sizeof(u8) * on_the_right);
  array->size--;
}

void print_array(Array *array) {
  printf("[");
  for (u64 i = 0; i < array->size; i++) {
    char final_char = i < array->size - 1 ? ',' : '\0';
    printf("%d%c", array->data[i], final_char);
  }
  printf("]\n");
}
