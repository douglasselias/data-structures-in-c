#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "types.c"

typedef struct Node Node;
struct Node {
  Node *next;
  void *value;
};

typedef struct {
  Node *first;
  Node *last;
  u64 size;
} Queue;

void enqueue(Queue *q, void *value) {
  Node *n = malloc(sizeof(Node));
  n->value = value;
  n->next = NULL;

  if (q->last == NULL) {
    q->first = n;
  } else {
    q->last->next = n;
  }

  q->last = n;
  q->size++;
}

void *dequeue(Queue *q) {
  if (q->first == NULL) {
    q->last = NULL;
    return NULL;
  }

  void *value = q->first->value;
  Node *second_node = q->first->next;
  free(q->first);
  q->first = second_node;
  q->size--;

  if (second_node == NULL) {
    q->last = NULL;
  }

  return value;
}
