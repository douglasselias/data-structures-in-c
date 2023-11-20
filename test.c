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

Test(string, join) {
  String *s0 = create_string("Hello");
  String *s1 = create_string(" World");

  String *result = join(s0, s1);

  cr_assert(strcmp(result->head, "Hello World") == 0);
}