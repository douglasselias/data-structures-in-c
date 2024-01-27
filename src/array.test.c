#include <criterion/criterion.h>

#include "arena.c"
#include "array.c"

Test(array, append) {
  Arena *arena = create_arena(4096);
  Array *array = create_array(arena, 10);

  for (u8 i = 0; i < 10; i++) {
    array_append(arena, array, i + 1);
  }
  // print_arena(arena);

  for (u8 i = 0; i < 10; i++) {
    array_append(arena, array, i + 11);
  }

  // print_array(array);
  // print_arena(arena);

  cr_assert(array->size == 20);
}

Test(array, remove_by_index) {
  Arena *arena = create_arena(4096);
  Array *array = create_array(arena, 10);

  for (u8 i = 0; i < 10; i++) {
    array_append(arena, array, i + 1);
  }
  // print_arena(arena);

  array_remove_by_index(array, 2);
  array_remove_by_index(array, 8);
  array_remove_by_index(array, 0);

  print_array(array);
  // print_arena(arena);

  cr_assert(array->size == 7);
}
