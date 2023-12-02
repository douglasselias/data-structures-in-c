#include <stdint.h>
#include <stdio.h>

#include "src/arena.c"
#include "src/queue.c"

typedef uint64_t u64;

typedef struct BinNode BinNode;
struct BinNode {
  BinNode *left;
  BinNode *right;
  int value;
};

void insert_node(BinNode *root, int value, Arena *arena) {
  BinNode *current = root;

  if (current->value == 0) {
    current->value = value;
    return;
  }

  if (value <= current->value) {
    if (current->left == NULL) {
      current->left = arena_alloc(arena, sizeof(BinNode));
      current->left->left = NULL;
      current->left->right = NULL;
      current->left->value = value;
    } else {
      insert_node(current->left, value, arena);
    }
  } else {
    if (current->right == NULL) {
      current->right = arena_alloc(arena, sizeof(BinNode));
      current->right->left = NULL;
      current->right->right = NULL;
      current->right->value = value;
    } else {
      insert_node(current->right, value, arena);
    }
  }
}

BinNode *remove_node(BinNode *root, int value) {
  if (root == NULL)
    return NULL;

  if (value < root->value) {
    root->left = remove_node(root->left, value);
  } else if (value > root->value) {
    root->right = remove_node(root->right, value);
  } else {
    // Node with only one child or no child
    if (root->left == NULL) {
      BinNode *new_root = root->right;
      // delete root;
      return new_root;
    } else if (root->right == NULL) {
      BinNode *new_root = root->left;
      // delete root;
      return new_root;
    }

    // Node with two children, find the in-order successor (smallest node in the
    // right subtree)
    BinNode *successor = root->right;
    while (root->left != NULL) {
      successor = root->left;
    }

    // Copy the in-order successor's data to this node
    root->value = successor->value;

    // Recursively delete the in-order successor
    root->right = remove_node(root->right, successor->value);
  }

  return root;
}

void traverse_pre_order(BinNode *root) {
  if (root == NULL)
    return;
  printf("Value: %d\n", root->value);
  traverse_pre_order(root->left);
  traverse_pre_order(root->right);
}
void traverse_in_order(BinNode *root) {
  if (root == NULL)
    return;
  traverse_in_order(root->left);
  printf("Value: %d\n", root->value);
  traverse_in_order(root->right);
}
void traverse_post_order(BinNode *root) {
  if (root == NULL)
    return;
  traverse_post_order(root->left);
  traverse_post_order(root->right);
  printf("Value: %d\n", root->value);
}

void traverse_depth_first(BinNode *root) {
  if (root == NULL)
    return;
  printf("Value: %d\n", root->value);
  traverse_depth_first(root->left);
  traverse_depth_first(root->right);
}

void traverse_breadth_first(BinNode *root) {
  Queue q = {0};
  enqueue(&q, (void *)root);

  while (q.size > 0) {
    BinNode *bin_node = dequeue(&q);
    printf("Value: %d\n", bin_node->value);

    if (bin_node->left != NULL)
      enqueue(&q, (void *)bin_node->left);
    if (bin_node->right != NULL)
      enqueue(&q, (void *)bin_node->right);
  }
}

int main() {
  Arena *arena = create_arena();
  BinNode *root = arena_alloc(arena, sizeof(BinNode));
  root->left = NULL;
  root->right = NULL;
  root->value = 0;

  int values[5] = {4, 9, 2, 8, 5};
  for (int i = 0; i < 5; i++) {
    insert_node(root, values[i], arena);
  }

  remove_node(root, 9);// root doesnt work

  // traverse_pre_order(root);
  // traverse_in_order(root);
  // traverse_post_order(root);
  // traverse_depth_first(root);
  traverse_breadth_first(root);
  return 0;
}