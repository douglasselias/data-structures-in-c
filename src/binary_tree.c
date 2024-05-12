#include "arena.c"

// typedef u8 bin_value;

typedef struct BinNode BinNode;
struct BinNode {
  BinNode *left;
  BinNode *right;
  u8 value;
};

BinNode* create_binary_tree(Arena* arena) {
  return alloc_arena(arena, sizeof(BinNode));
}

void insert_binary_tree(Arena* arena, BinNode* root, u8 value) {
  if(root->value == 0) {
    root->value = value;
    return;
  }

  if(value < root->value) {
    if(root->left != NULL) {
      return insert_binary_tree(arena, root->left, value);
    }

    BinNode* new_node = alloc_arena(arena, sizeof(BinNode));
    new_node->value = value;
    root->left = new_node;
  } else {
    if(root->right != NULL) {
      return insert_binary_tree(arena, root->right, value);
    }

    BinNode* new_node = alloc_arena(arena, sizeof(BinNode));
    new_node->value = value;
    root->right = new_node;
  }
}

bool search_binary_tree(BinNode* root, u8 value) {
  if(root->value == value) {
    return true;
  }

  if(value < root->value) {
    if(root->left == NULL) {
      return false;
    }

    return search_binary_tree(root->left, value);
  } else {
    if(root->right == NULL) {
      return false;
    }

    return search_binary_tree(root->right, value);
  }
}

void remove_binary_tree(Arena* arena, BinNode** root, u8 value) {
  if((*root)->value == value) {
    if((*root)->left != NULL && (*root)->right != NULL) {
      u8 tmp_value = (*root)->right->value;
      *root = (*root)->left;
      insert_binary_tree(arena, root, tmp_value);
    } else if((*root)->left != NULL) {
      *root = (*root)->left;
    } else if((*root)->right != NULL) {
      *root = (*root)->right;
    } else {
      // printf("Root Value: %d, Value: %d\n", root->value, value);
      *root = NULL;
      // memset(root, NULL, sizeof(BinNode));
      // root = NULL;
      // printf("Root Value: %d\n", root->value);
    }
    return;
  }

  if(value < (*root)->value) {
    if((*root)->left == NULL) {
      return;
    }

    puts("is on the left");
    remove_binary_tree(arena, &(*root)->left, value);
  } else {
    if((*root)->right == NULL) {
      return;
    }

    remove_binary_tree(arena, &(*root)->right, value);
  }
}

void print_binary_tree(BinNode* root) {
  if(root == NULL) return;
  printf("%d, ", root->value);
  print_binary_tree(root->left);
  print_binary_tree(root->right);
}
