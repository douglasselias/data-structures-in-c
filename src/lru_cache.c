// Code based on
// https://github.com/trekhleb/javascript-algorithms/blob/master/src/data-structures/lru-cache/images/lru-cache.jpg

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int u32;
typedef unsigned int u64;
#define LRU_MAX_HASH_SIZE 100

u64 hash_key(const char* key) {
  u64 hash = 0;

  while(*key) {
    hash = hash * 31 + *key;
    key++;
  }

  return hash % LRU_MAX_HASH_SIZE;
}

typedef struct Node Node;
struct Node {
  char* key;
  u64 value;
  Node* previous;
  Node* next;
};

typedef struct LRUCache LRUCache;
struct LRUCache {
  u64 capacity;
  Node* nodes_map[LRU_MAX_HASH_SIZE];
  u64 size;
  Node head;
  Node tail;
};

void evict(LRUCache* lru, Node* node) {
  free(lru->nodes_map[hash_key(node->key)]);
  lru->nodes_map[hash_key(node->key)] = NULL;
  lru->size--;

  Node* previous_node = node->previous;
  Node* next_node = node->next;

  // If one and only node
  if(previous_node == &(lru->head) && next_node == &(lru->tail)) {
    lru->head.next = (Node*)malloc(sizeof(Node));
    lru->tail.previous = (Node*)malloc(sizeof(Node));
    lru->size = 0;
    return;
  }

  // If this is a head node
  if(previous_node == &(lru->head)) {
    next_node->previous = &(lru->head);
    lru->head.next = next_node;
    return;
  }

  // If this is a tail node
  if(next_node == &(lru->tail)) {
    previous_node->next = &(lru->tail);
    lru->tail.previous = previous_node;
    return;
  }

  // If the node is in the middle
  previous_node->next = next_node;
  next_node->previous = previous_node;
}

void append(LRUCache *lru, Node* node) {
  lru->nodes_map[hash_key(node->key)] = node;

  if(lru->head.next == NULL) {
    // First node to append
    lru->head.next = node;
    lru->tail.previous = node;
    node->previous = &(lru->head);
    node->next = &(lru->tail);
  } else {
    // Append to an existing tail
    Node* old_tail = lru->tail.previous;
    old_tail->next = node;
    node->previous = old_tail;
    node->next = &(lru->tail);
    lru->tail.previous = node;
  }

  lru->size++;

  if(lru->size > lru->capacity) {
    evict(lru, lru->head.next);
  }
}

void promote(LRUCache* lru, Node* node) {
  Node* tmp_node = (Node*)malloc(sizeof(Node));
  memcpy(tmp_node, node, sizeof(Node));
  evict(lru, node);
  append(lru, tmp_node);
}

u64 get(LRUCache* lru, char* key) {
  u64 hash = hash_key(key);
  if(lru->nodes_map[hash] == NULL) return 0;
  Node* node = lru->nodes_map[hash];
  promote(lru, node);
  return node->value;
}

void set(LRUCache *lru, const char* key, u64 value) {
  u64 hash = hash_key(key);

  if(lru->nodes_map[hash] != NULL) {
    Node* node = lru->nodes_map[hash];
    node->value = value;
    promote(lru, node);
  } else {
    Node* node = (Node*)malloc(sizeof(Node));
    size_t key_length = strlen(key);
    node->key = (char*)malloc(sizeof(char) * (key_length + 1));
    strcpy(node->key, key);
    node->key[key_length] = '\0';
    node->value = value;
    append(lru, node);
  }
}

void print_lru(LRUCache* lru) {
  u64 i = 0;
  for(Node* current = lru->head.next;
      current != &(lru->tail);
      current = current->next) {
    printf("[%s:%d]", current->key, current->value);
    if(i++ < lru->size - 1) printf(" <-> ");
  }
  puts("\n");
}

int main() {
  LRUCache lru = {};
  lru.capacity = 3;

  puts("\nLRU Cache\n");

  set(&lru, "A", 1);
  print_lru(&lru);
  set(&lru, "B", 2);
  print_lru(&lru);
  set(&lru, "C", 3);
  print_lru(&lru);
  set(&lru, "D", 4);
  print_lru(&lru);
  set(&lru, "C", 5);
  print_lru(&lru);
  printf("B:%d\n\n", get(&lru, "B"));
  print_lru(&lru);
  printf("C:%d\n\n", get(&lru, "C"));
  print_lru(&lru);
  set(&lru, "E", 6);
  print_lru(&lru);
  printf("D:%d\n\n", get(&lru, "D"));
  print_lru(&lru);
}