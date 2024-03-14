// Copied from:
// https://gist.github.com/rexim/b5b0c38f53157037923e7cdd77ce685d

#include <stdio.h>
#include <stdlib.h>

#define da_append(xs, x)                                                         \
  do {                                                                           \
    if ((xs)->count >= (xs)->capacity) {                                         \
      if ((xs)->capacity == 0) (xs)->capacity = 256;                             \
      else (xs)->capacity *= 2;                                                  \
      (xs)->items = realloc((xs)->items, (xs)->capacity * sizeof(*(xs)->items)); \
    }                                                                            \
                                                                                 \
    (xs)->items[(xs)->count++] = (x);                                            \
  } while (0)

typedef struct {
    int *items;
    size_t count;
    size_t capacity;
} Numbers;

int main(void) {
    Numbers xs = {0};
    for (int x = 0; x < 10; ++x) da_append(&xs, x);
    for (size_t i = 0; i < xs.count; ++i) printf("%d\n", xs.items[i]);
    return 0;
}