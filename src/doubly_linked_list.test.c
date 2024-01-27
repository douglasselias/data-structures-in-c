#include <criterion/criterion.h>

#include "arena.c"
#include "doubly_linked_list.c"

Test(hash_table, insert_get_delete) {
  Arena *arena = create_arena(4096);
  DLList *dllist = create_dllist(arena);

  insert_dllist(arena, dllist, 0xea);
  insert_dllist(arena, dllist, 0xfa);
  insert_dllist(arena, dllist, 0xeb);

  print_dllist(dllist);

  delete_dllist(dllist, 0xfa);

  print_dllist(dllist);

  cr_assert(get_dllist(dllist, 0xfa) == false);
  cr_assert(get_dllist(dllist, 0xea) == true);
}
