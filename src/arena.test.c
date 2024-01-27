#include <criterion/criterion.h>

#include "arena.c"

Test(arena, write_more_than_allowed) {
  Arena *arena = create_arena(4096);
  u8 *ptr_u8 = alloc_arena(arena, sizeof(u8));
  *ptr_u8++ = 0xff;
  *ptr_u8++ = 0b00000011;
  *ptr_u8++ = 5;

  arena->current++;
  arena->current++;

  print_arena(arena);

  cr_assert(arena->current == arena->start + 3 * sizeof(u8));
}

Test(arena, write_correctly) {
  Arena *arena = create_arena(4096);
  u8 *p0 = alloc_arena(arena, sizeof(u8));
  *p0 = 0xff;
  u8 *p1 = alloc_arena(arena, sizeof(u8));
  *p1 = 0b00000011;
  u8 *p2 = alloc_arena(arena, sizeof(u8));
  *p2 = 5;

  format_as_hex = false;
  print_arena(arena);

  cr_assert(arena->current == arena->start + 3 * sizeof(u8));
}

Test(arena, store_floats) {
  Arena *arena = create_arena(4096);
  f32 *p = alloc_arena(arena, sizeof(f32));
  *p = 3.1415927;

  print_arena(arena);

  cr_assert(arena->current == arena->start + 1 * sizeof(f32));
}
