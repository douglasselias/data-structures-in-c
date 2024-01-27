#include <criterion/criterion.h>

#include "arena.c"
#include "hash_table.c"

Test(hash_table, insert_get_delete) {
  Arena *arena = create_arena(4096);
  HashTable *ht = create_ht(arena, 8);

  insert_ht(ht, (u8 *)"hello", 0xff);
  insert_ht(ht, (u8 *)"world", 0xda);
  insert_ht(ht, (u8 *)"!!!!!", 0xcb);

  delete_ht(ht, (u8 *)"hello");

  print_ht(ht);

  cr_assert(get_ht(ht, (u8 *)"!!!!!") == 0xcb);
  cr_assert(get_ht(ht, (u8 *)"hello") == 0);
}
