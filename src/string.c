#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arena.c"

typedef struct String String;
struct String {
  char *head;
  int size;
};

String *create_string(char *string) {
  String *str = malloc(sizeof(String));
  int size = 0;
  char *curr_char = string;

  while (*curr_char != '\0') {
    curr_char++;
    size++;
  }

  str->head = string;
  str->size = size;
  return str;
}

String *join_strings(String *a, String *b) {
  String *str = malloc(sizeof(String));
  str->size = a->size + b->size;
  char *c = malloc(sizeof(char) * str->size);
  strcpy(c, a->head);
  strcpy(c + a->size, b->head);
  str->head = c;
  return str;
}

String *arena_create_string(Arena *arena, char *string) {
  String *str = arena_alloc(arena, sizeof(String));
  int size = 0;
  char *curr_char = string;

  while (*curr_char != '\0') {
    curr_char++;
    size++;
  }

  str->head = string;
  str->size = size;
  return str;
}

String *arena_join_strings(Arena *arena, String *a, String *b) {
  String *str = arena_alloc(arena, sizeof(String));
  str->size = a->size + b->size;
  char *c = malloc(sizeof(char) * str->size);
  strcpy(c, a->head);
  strcpy(c + a->size, b->head);
  str->head = c;
  return str;
}

void prints(String *s) { printf("%s", s->head); }
