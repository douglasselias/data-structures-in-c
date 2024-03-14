#pragma once

#include "arena.c"

typedef struct Node Node;
struct Node {
  Node *previous;
  Node *next;
  u8 value;
};

typedef struct {
  Node *first;
  Node *last;
} DLList;

DLList *create_dllist(Arena *arena) {
  DLList *dllist = alloc_arena(arena, sizeof(DLList));
  dllist->first = NULL;
  dllist->last = NULL;
  return dllist;
}

void insert_dllist(Arena *arena, DLList *dllist, u8 value) {
  Node *new_node = alloc_arena(arena, sizeof(Node));
  new_node->value = value;
  new_node->next = NULL;

  if (dllist->first == NULL) {
    // The list is empty, so the new node becomes the first and last node
    dllist->first = new_node;
    dllist->last = new_node;
  } else {
    // Traverse the list to find the last node
    Node *current = dllist->first;
    while (current->next != NULL) {
      current = current->next;
    }

    // Link the current last node to the new node
    current->next = new_node;
    new_node->previous = current;

    // Update the last pointer to the new node
    dllist->last = new_node;
  }
}

bool get_dllist(DLList *dllist, u8 value) {
  for (Node *current = dllist->first; current != NULL;
       current = current->next) {
    if (current->value == value)
      return true;
  }
  return false;
}

void delete_dllist(DLList *dllist, u8 value) {
  Node *current = dllist->first;
  for (Node *current = dllist->first; current->next != NULL;
       current = current->next) {
    if (current->value == value) {
      current->previous->next = current->next;
      current->next->previous = current->previous;
      return;
    }
  }
}

void print_dllist(DLList *dllist) {
  puts("DLList");
  for (Node *current = dllist->first; current != NULL; current = current->next) {
    printf("0x%x\n", current->value);
  }
}