#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct String String;
struct String {
  char *head;
  int size;
};

String *create_string(char *s) {
  String *str = malloc(sizeof(String));
  int size = 0;
  char *curr_char = s;

  while (*curr_char != '\0') {
    curr_char++;
    size++;
  }

  str->head = s;
  str->size = size;
  return str;
}

String *join(String *a, String *b) {
  String *str = malloc(sizeof(String));
  str->size = a->size + b->size;
  char *c = malloc(sizeof(char) * str->size);
  strcpy(c, a->head);
  strcpy(c + a->size, b->head);
  str->head = c;
  return str;
}

void prints(String *s) { printf("%s", s->head); }
