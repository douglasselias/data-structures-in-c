#include <criterion/criterion.h>
#include <stdint.h>

#include "src/queue.c"
#include "src/string.c"

Test(queue, enqueue) {
  Queue q = {0};

  enqueue(&q, (void *)2);
  enqueue(&q, (void *)4);
  enqueue(&q, (void *)6);

  cr_assert(q.size == 3);

  int *first = dequeue(&q);
  int *second = dequeue(&q);
  int *third = dequeue(&q);

  cr_assert((intptr_t)first == 2);
  cr_assert((intptr_t)second == 4);
  cr_assert((intptr_t)third == 6);
  cr_assert(q.size == 0);
}

Test(string, join_strings) {
  String *s0 = create_string("Hello");
  String *s1 = create_string(" World");

  String *result = join_strings(s0, s1);

  cr_assert(strcmp(result->head, "Hello World") == 0);
}

Test(arena, join_strings) {
  Arena *arena = create_arena();
  String *s0 = arena_create_string(arena, "Hello");
  String *s1 = arena_create_string(arena, " World");

  String *result = arena_join_strings(arena, s0, s1);

  cr_assert(strcmp(result->head, "Hello World") == 0);
}

Test(arena, reset) {
  Arena *arena = create_arena();
  String *s0 = arena_create_string(arena, "Hello");
  arena_reset(arena);
  arena_create_string(arena, " World");

  cr_assert(strcmp(s0->head, " World") == 0);
}