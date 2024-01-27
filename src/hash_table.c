#pragma once

#include "arena.c"

typedef struct {
  u64 count;
  u64 max_size;
  u8 *table;
} HashTable;

HashTable *create_ht(Arena *arena, u64 size) {
  HashTable *ht = alloc_arena(arena, sizeof(HashTable));
  ht->count = 0;
  ht->max_size = size;
  ht->table = alloc_arena(arena, size);
  return ht;
}

u64 hash_key(u8 *key) {
  u64 hash = 0;

  while (*key) {
    hash += *key;
    key++;
  }

  return hash % 8;
}

void insert_ht(HashTable *ht, u8 *key, u8 value) {
  u64 hash = hash_key(key);
  printf("Hash: %ld\n", hash);
  ht->table[hash] = value;
  ht->count++;
}

u8 get_ht(HashTable *ht, u8 *key) {
  u64 hash = hash_key(key);
  return ht->table[hash];
}

void delete_ht(HashTable *ht, u8 *key) {
  u64 hash = hash_key(key);
  ht->table[hash] = 0;
}

static bool format_as_hex_ht = true;
void print_ht(HashTable *ht) {
  u8 arena_width = 8;
  u64 line = 1;
  for (u8 *iterator = ht->table; iterator < (ht->table + ht->max_size);
       iterator++) {
    char *format = format_as_hex_ht ? "0x%02x %c" : "0x%08b %c";
    char final_char = line % arena_width == 0 ? '\n' : '\0';
    printf(format, *iterator, final_char);
    line++;
  }
  puts("");
}
