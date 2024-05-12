#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "types.c"

typedef struct {
  // Arena *previous;
  // Arena *next;
  u8 *start;
  u8 *used;
  u8 *end;
} Arena;

/// @note: size should be size_t
Arena *create_arena(u64 size) {
  Arena *arena = malloc(sizeof(Arena));
  arena->start = malloc(size);
  arena->used = arena->start;
  arena->end = arena->start + size;
  return arena;
}

void destroy_arena(Arena *arena) {
  free(arena->start);
  free(arena);
  arena = NULL;
}

void *alloc_arena(Arena *arena, u64 size) {
  if(arena->used + size <= arena->end) {
    void *block = arena->used;
    arena->used += size;
    /// @note: the caller can write more data than allowed
    return block;
  } 

  fprintf(stderr, "Arena out of memory\n");
  exit(EXIT_FAILURE);
}

void reset_arena(Arena *arena) {
  arena->used = arena->start;
}

static bool format_as_hex = true;
void print_arena(Arena *arena) {
  u8 arena_width = 8;
  u64 line = 1;
  for(u8 *iterator = arena->start; iterator < arena->used; iterator++) {
    char *format = format_as_hex ? "0x%02x %c" : "0x%08b %c";
    char final_char = line % arena_width == 0 ? '\n' : '\0';
    printf(format, *iterator, final_char);
    line++;
  }
  puts("");
}