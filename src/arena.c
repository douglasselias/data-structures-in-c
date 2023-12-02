/// infinite size arena (chain upgrades)
/// using the mmu (no malloc)
/// dynamic array that never relocates
/// support sub-lifetime (pool allocator using free list) (malloc?)
/// visualization && debugging (push & pop logs, timestamp)

#pragma once

#include <stdio.h>
#include <stdlib.h>

const int arena_size = 4096;

typedef struct Arena Arena;
struct Arena {
  char *start;
  char *current;
  char *end;
};

Arena *create_arena() {
  Arena *arena = malloc(sizeof(Arena));
  arena->start = malloc(arena_size);
  arena->current = arena->start;
  arena->end = arena->start + arena_size;
  return arena;
}

void *arena_alloc(Arena *arena, size_t size) {
  if (arena->current + size <= arena->end) {
    void *block = arena->current;
    arena->current += size;
    return block;
  } else {
    fprintf(stderr, "Arena out of memory\n");
    exit(EXIT_FAILURE);
  }
}

void arena_reset(Arena *arena) { arena->current = arena->start; }

void destroy_arena(Arena *arena) { free(arena->start); }

void print_arena(Arena *arena) {
  int line = 1;
  for (char *iterator = arena->start; iterator < arena->current; iterator++) {
    printf("0x%08x %c", *iterator, line % 8 == 0 ? '\n' : '\0');
    line++;
  }
  puts("");
}