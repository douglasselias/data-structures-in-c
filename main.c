#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
struct Node {
  Node *next;
  int value;
};

typedef struct {
  Node *first;
  Node *last;
  int size;
} Queue;

void enqueue(Queue *q, int value) {
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

int dequeue(Queue *q) {
  if (q->first == NULL) {
    q->last = NULL;
    return 0;
  }

  int value = q->first->value;
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

  enqueue(&q, 2);
  enqueue(&q, 4);
  enqueue(&q, 6);
  printf("Size of Queue after queuing: %d\n", q.size);

  printf("Dequeued value: %d\n", dequeue(&q));
  printf("Dequeued value: %d\n", dequeue(&q));
  printf("Dequeued value: %d\n", dequeue(&q));
  printf("Dequeued value: %d\n", dequeue(&q));
  printf("Size of Queue after dequeuing: %d\n", q.size);

  enqueue(&q, 10);
  printf("Dequeued value: %d\n", dequeue(&q));

  return 0;
}