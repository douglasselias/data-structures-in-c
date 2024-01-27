#pragma once

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "arena.c"

typedef struct {
  u8 *start;
  u8 *current;
  u8 *end;
  u64 size;
} Stack;

Stack *create_stack(Arena *arena, u64 size) {
  Stack *stack = alloc_arena(arena, sizeof(Stack));
  stack->start = alloc_arena(arena, size);
  stack->current = stack->start;
  stack->end = stack->start + size;
  stack->size = 0;
  return stack;
}

void push(Stack *stack, u8 *value, u64 size) {
  memcpy(stack->current, value, size);
  stack->current += size;
  stack->size++;
}

u8 *pop(Stack *stack, u64 size) {
  stack->size--;
  u8 *value = malloc(sizeof(u8));
  stack->current -= size;
  memcpy(value, stack->current, size);
  return value;
}

static bool format_as_hex_stack = true;
void print_stack(Stack *stack) {
  puts("--- Stack --------");
  u8 arena_width = 8;
  u64 line = 1;
  for (u8 *iterator = stack->start; iterator < stack->current; iterator++) {
    char *format = format_as_hex_stack ? "0x%02x %c" : "0x%08b %c";
    char final_char = line % arena_width == 0 ? '\n' : '\0';
    printf(format, *iterator, final_char);
    line++;
  }
  puts("\n------------------");
}