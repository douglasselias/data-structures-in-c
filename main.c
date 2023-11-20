#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
struct Node {
  Node *next;
  void *value;
};

typedef struct {
  Node *first;
  Node *last;
  int size;
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

int main() {
  Queue q = {0};

  enqueue(&q, (void *)2);
  enqueue(&q, (void *)4);
  enqueue(&q, (void *)6);
  printf("Size of Queue after queuing: %d\n", q.size);

  printf("Dequeued value: %d\n", (int)(intptr_t)dequeue(&q));
  printf("Dequeued value: %d\n", (int)(intptr_t)dequeue(&q));
  printf("Dequeued value: %d\n", (int)(intptr_t)dequeue(&q));
  printf("Dequeued value: %d\n", (int)(intptr_t)dequeue(&q));
  printf("Size of Queue after dequeuing: %d\n", q.size);

  enqueue(&q, (void *)10);
  printf("Dequeued value: %ld\n", (intptr_t)dequeue(&q));

  enqueue(&q, (void *)"Hello\0");
  printf("Dequeued value: %s\n", (char*)dequeue(&q));

  return 0;
}