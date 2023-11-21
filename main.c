#include "src/arena.c"
#include "src/queue.c"
#include "src/string.c"

typedef int8_t u8;

int main() {
  Arena *arena = create_arena();

  u8 *my_array = arena_alloc(arena, 5 * sizeof(u8));
  for (int i = 0; i < 5; i++) {
    my_array[i] = (i + 1) * 10;
  }

  for (int i = 0; i < 5; i++) {
    printf("Value: %d\n", my_array[i]);
  }

  arena_reset(arena);

  String *s0 = arena_create_string(arena, "Hello");
  prints(s0);
  puts("");

  print_arena(arena);
  destroy_arena(arena);
  return 0;
}