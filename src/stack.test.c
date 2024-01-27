#include <criterion/criterion.h>

#include "stack.c"

Test(stack, push_pop_correctly) {
  u64 stack_size = 512;
  Arena *stack_arena = create_arena(sizeof(Stack) + stack_size);
  Stack *stack = create_stack(stack_arena, stack_size);

  u8 *v = malloc(sizeof(u8));
  *v = 0xab;
  push(stack, v, sizeof(u8));
  *v = 0xff;
  push(stack, v, sizeof(u8));
  *v = 0xbc;
  push(stack, v, sizeof(u8));

  print_stack(stack);

  u8 *value = NULL;
  value = pop(stack, sizeof(u8));
  printf("Pop: 0x%x\n", *value);
  value = pop(stack, sizeof(u8));
  printf("Pop: 0x%x\n", *value);

  print_stack(stack);
  // print_arena(arena);

  cr_assert(stack->size == 1);
  // destroy_arena(stack_arena);
}
