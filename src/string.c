#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.c"
#include "arena.c"

typedef struct {
  u8 *head;
  u64 size;
} String;

String *create_string(u8 *text) {
  String *string = malloc(sizeof(String));
  string->head = text;
  string->size = strlen((char*)text);
  return string;
}

String *join_strings(String *a, String *b) {
  String *string = malloc(sizeof(String));
  string->size = a->size + b->size;
  u8 *c = malloc(sizeof(a->head) * string->size);
  strcpy((char*)c, (char*)a->head);
  strcpy((char*)c + a->size, (char*)b->head);
  string->head = c;
  return string;
}

String *arena_create_string(Arena *arena, u8 *text) {
  String *string = alloc_arena(arena, sizeof(String));
  string->head = text;
  string->size = strlen((char*)text);
  return string;
}

String *arena_join_strings(Arena *arena, String *a, String *b) {
  String *str = alloc_arena(arena, sizeof(String));
  str->size = a->size + b->size;
  char *c = malloc(sizeof(a->head) * str->size);
  strcpy(c, (char*)a->head);
  strcpy(c + a->size, (char*)b->head);
  str->head = (u8*)c;
  return str;
}

void prints(String *s) { printf("%s", s->head); }
