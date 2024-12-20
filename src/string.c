#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "types.c"
#include "arena.c"

typedef struct {
  u8 *head;
  u64 size;
} String;

#define STR(name, text) String name = {(u8*)text, strlen(text)}

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

void prints(String s) {
  printf("%.*s", (i32)s.size, s.head);
}

String str(u8 *str, u64 size) {
  String result = {str, size};
  return (result);
}

void to_lower(String *s) {
  u64 size = s->size;
  while(size--) {
    s->head[size] = tolower(s->head[size]);
  }
}

void to_upper(String *s) {
  u64 size = s->size;
  while(size--) {
    s->head[size] = toupper(s->head[size]);
  }
}

void to_upper_str(char *s) {
  u64 size = strlen(s);
  while(size--) {
    s[size] = toupper(s[size]);
  }
}

String concat(String a, String b) {
  String result = {};
  result.size = a.size + b.size;
  result.head = (u8*)malloc(sizeof(u8) * result.size);
  memcpy(result.head         , a.head, a.size);
  memcpy(result.head + a.size, b.head, b.size);
  return result;
}

String** split(String text, u8 delim, u64 *size) {
  u64 delim_count = 0;
  for(u64 i = 0; i < text.size; i++) {
    if(text.head[i] == delim) delim_count++;
  }

  *size = delim_count + 1;
  String **strings = (String**)malloc(sizeof(String*) * (*size));
  u64 strings_index = 0;

  u64 last_delim_index = 0;
  for(u64 i = 0; i <= text.size; i++) {
    if(text.head[i] == delim || i == text.size) {
      String *s = (String*)malloc(sizeof(String));
      s->size = i - last_delim_index;
      s->head = (u8*)malloc(sizeof(u8) * s->size);
      memcpy(s->head, text.head + last_delim_index, s->size);
      last_delim_index = i+1;
      strings[strings_index++] = s;
    }
  }

  return strings;
}

bool string_equal(String a, String b) {
  if(a.size != b.size) return false;

  bool is_equal = true;
  while(a.size--) {
    if(a.head[a.size] != b.head[a.size]) {
      is_equal = false;
      break;
    }
  }

  return is_equal;
}

#include "greatest.h"

/* A test runs various assertions, then calls PASS(), FAIL(), or SKIP(). */
TEST x_should_equal_1(void) {
    int x = 1;
    /* Compare, with an automatic "1 != x" failure message */
    ASSERT_EQ(1, x);

    /* Compare, with a custom failure message */
    ASSERT_EQm("Yikes, x doesn't equal 1", 1, x);

    /* Compare, and if they differ, print both values,
     * formatted like `printf("Expected: %d\nGot: %d\n", 1, x);` */
    ASSERT_EQ_FMT(1, x, "%d");
    PASS();
}

TEST strings_should_be_equal(void) {
  STR(hello, "Hello");
  ASSERT(strcmp((const char*)hello.head, "World") != 0);
  PASS();
}

TEST should_split_strings(void) {
  STR(a, "Nintendo");
  STR(b, " ");
  STR(c, "Switch");
  String words[] = {a,b,c};

  STR(result, "");
  for(u8 i = 0; i < 3; i++) {
    result = concat(result, words[i]);
  }

  u64 ss_size = 0;
  String **ss = split(result, ' ', &ss_size);
  ASSERT(string_equal(*ss[0], a));
  ASSERT(string_equal(*ss[1], c));
  PASS();
}

/* Suites can group multiple tests with common setup. */
SUITE(the_suite) {
    RUN_TEST(x_should_equal_1);
    RUN_TEST(strings_should_be_equal);
    RUN_TEST(should_split_strings);
}

/* Add definitions that need to be in the test runner's main file. */
GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();      /* command-line options, initialization. */

    /* Individual tests can be run directly in main, outside of suites. */
    /* RUN_TEST(x_should_equal_1); */

    /* Tests can also be gathered into test suites. */
    RUN_SUITE(the_suite);

    GREATEST_MAIN_END();        /* display results */
}

// int main() {
//   // STR(hello, "Hello");
//   // prints(hello);
//   // puts("");

//   // to_upper(&hello);
//   // prints(hello);

//   // puts("");

//   STR(a, "Nintendo");
//   STR(b, " ");
//   STR(c, "Switch");

//   String words[] = {a,b,c};
//   STR(result, "");
//   for(u8 i = 0; i < 3; i++) {
//     result = concat(result, words[i]);
//   }

//   // prints(result);

//   u64 ss_size = 0;
//   String **ss = split(result, ' ', &ss_size);
//   // printf("Size: %lld\n", ss_size);

//   // String z = *(ss[0]);
//   // prints(z);

//   for(u64 i = 0; i < ss_size; i++) {
//     prints(*ss[i]);
//     puts("");
//   }

//   return 0;
// }


// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// typedef struct {
//     char *buffer;
//     size_t size;
//     size_t capacity;
// } StringBuilder;

// // Initialize a string builder
// void sb_init(StringBuilder *sb) {
//     sb->size = 0;
//     sb->capacity = 16;  // initial capacity
//     sb->buffer = (char *)malloc(sb->capacity * sizeof(char));
//     sb->buffer[0] = '\0';  // Null-terminate the string initially
// }

// // Append a string to the builder
// void sb_append(StringBuilder *sb, const char *str) {
//     size_t len = strlen(str);
//     // Resize the buffer if necessary
//     if (sb->size + len + 1 > sb->capacity) {
//         sb->capacity = (sb->size + len + 1) * 2;  // Double the capacity
//         sb->buffer = (char *)realloc(sb->buffer, sb->capacity * sizeof(char));
//     }
//     // Append the string
//     strcpy(sb->buffer + sb->size, str);
//     sb->size += len;
// }

// // Free the memory used by the builder
// void sb_free(StringBuilder *sb) {
//     free(sb->buffer);
// }

// int main() {
//     StringBuilder sb;
//     sb_init(&sb);

//     sb_append(&sb, "Hello, ");
//     sb_append(&sb, "world!");
    
//     printf("%s\n", sb.buffer);  // Output: Hello, world!

//     sb_free(&sb);
//     return 0;
// }
