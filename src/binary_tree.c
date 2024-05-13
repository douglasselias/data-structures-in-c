#include "arena.c"
#include "queue.c"

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
      insert_binary_tree(arena, *root, tmp_value);
    } else if((*root)->left != NULL) {
      *root = (*root)->left;
    } else if((*root)->right != NULL) {
      *root = (*root)->right;
    } else {
      *root = NULL;
    }
    return;
  }

  if(value < (*root)->value) {
    if((*root)->left == NULL) {
      return;
    }

    remove_binary_tree(arena, &(*root)->left, value);
  } else {
    if((*root)->right == NULL) {
      return;
    }

    remove_binary_tree(arena, &(*root)->right, value);
  }
}

#define MAX(i, j) (((i) > (j)) ? (i) : (j))
u64 binary_tree_height(BinNode* root) {
  if(root == NULL) return 0;
  return 1 + MAX(binary_tree_height(root->left), binary_tree_height(root->right));
}

void print_binary_tree(BinNode* root) {
  /// @note: this is dfs
  if(root == NULL) return;
  printf("%d, ", root->value);
  print_binary_tree(root->left);
  print_binary_tree(root->right);
}

void print_binary_tree_bf(BinNode* root) {
  Queue q = {0};
  enqueue(&q, root);
  // u64 line = 0;

  while(q.size > 0) {
    BinNode* current_node = dequeue(&q);
    if(current_node == NULL) break;
    printf("%d", current_node->value);

    if(current_node->left != NULL) {
      enqueue(&q, current_node->left);
    }

    if(current_node->right != NULL) {
      enqueue(&q, current_node->right);
    }
  }
}
