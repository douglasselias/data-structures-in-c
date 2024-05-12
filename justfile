just:
  mkdir -p build && clang -std=c99 -Wall -Wextra -lm -g3 main.c -o ./build/main && ./build/main

test:
  mkdir -p build && clang -std=c99 -Wall -Wextra -g3 -lcriterion src/binary_tree.test.c -o ./build/test && ./build/test

debug:
  gdb ./build/test core