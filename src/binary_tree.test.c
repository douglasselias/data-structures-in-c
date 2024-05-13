#include <criterion/criterion.h>

#include "binary_tree.c"

Test(binary_tree_test, insert_node_correctly) {
  Arena *binary_tree_arena = create_arena(sizeof(BinNode) * 10);
  BinNode *binary_tree = create_binary_tree(binary_tree_arena);

  insert_binary_tree(binary_tree_arena, binary_tree, 5);
  insert_binary_tree(binary_tree_arena, binary_tree, 2);
  insert_binary_tree(binary_tree_arena, binary_tree, 7);

  // print_binary_tree(binary_tree);

  cr_assert(binary_tree->value == 5);
  cr_assert(binary_tree->left->value == 2);
  cr_assert(binary_tree->right->value == 7);

  destroy_arena(binary_tree_arena);
}

Test(binary_tree_test, search_node_correctly) {
  Arena *binary_tree_arena = create_arena(sizeof(BinNode) * 10);
  BinNode *binary_tree = create_binary_tree(binary_tree_arena);

  insert_binary_tree(binary_tree_arena, binary_tree, 5);
  insert_binary_tree(binary_tree_arena, binary_tree, 2);
  insert_binary_tree(binary_tree_arena, binary_tree, 7);
  insert_binary_tree(binary_tree_arena, binary_tree, 1);
  insert_binary_tree(binary_tree_arena, binary_tree, 9);

  // print_binary_tree(binary_tree);

  cr_assert(search_binary_tree(binary_tree, 1) == true);
  cr_assert(search_binary_tree(binary_tree, 9) == true);
  cr_assert(search_binary_tree(binary_tree, 10) == false);

  destroy_arena(binary_tree_arena);
}

Test(binary_tree_test, remove_node_correctly) {
  Arena *binary_tree_arena = create_arena(sizeof(BinNode) * 10);
  BinNode *binary_tree = create_binary_tree(binary_tree_arena);

  insert_binary_tree(binary_tree_arena, binary_tree, 5);
  insert_binary_tree(binary_tree_arena, binary_tree, 2);
  insert_binary_tree(binary_tree_arena, binary_tree, 7);
  insert_binary_tree(binary_tree_arena, binary_tree, 6);
  insert_binary_tree(binary_tree_arena, binary_tree, 8);

  remove_binary_tree(binary_tree_arena, &binary_tree, 2);
  remove_binary_tree(binary_tree_arena, &binary_tree, 7);
  // remove_binary_tree(binary_tree_arena, binary_tree, 9);

  print_binary_tree_bf(binary_tree);
  // printf("Height: %lu\n",binary_tree_height(binary_tree));

  cr_assert(search_binary_tree(binary_tree, 2) == false);
  cr_assert(search_binary_tree(binary_tree, 7) == false);
  cr_assert(search_binary_tree(binary_tree, 6) == true);

  destroy_arena(binary_tree_arena);
}
