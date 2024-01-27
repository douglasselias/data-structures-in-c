#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "types.c"

typedef struct {
  u8 *start;
  u8 *current;
  u8 *end;
  // Arena *previous;
  // Arena *next;
} Arena;

Arena *create_arena(u64 size) {
  Arena *arena = malloc(sizeof(Arena));
  arena->start = malloc(size);
  arena->current = arena->start;
  arena->end = arena->start + size;
  return arena;
}

void destroy_arena(Arena *arena) {
  free(arena->start);
  free(arena);
  arena = NULL;
}

void *alloc_arena(Arena *arena, u64 size) {
  if (arena->current + size <= arena->end) {
    void *block = arena->current;
    arena->current += size;
    /// @note: the caller can write more data than allowed
    return block;
  } else {
    /// @note: change to assert?
    fprintf(stderr, "Arena out of memory\n");
    exit(EXIT_FAILURE);
  }
}

void reset_arena(Arena *arena) { arena->current = arena->start; }

static bool format_as_hex = true;
void print_arena(Arena *arena) {
  u8 arena_width = 8;
  u64 line = 1;
  for (u8 *iterator = arena->start; iterator < arena->current; iterator++) {
    char *format = format_as_hex ? "0x%02x %c" : "0x%08b %c";
    char final_char = line % arena_width == 0 ? '\n' : '\0';
    printf(format, *iterator, final_char);
    line++;
  }
  puts("");
}