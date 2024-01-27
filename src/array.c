#include "arena.c"

typedef struct {
  int size;
  char *data;
  Arena *arena;
} Array;

void array_append(char value, Array *array) {
  if (array->data == NULL) {
    array->data = alloc_arena(array->arena, sizeof(char));
    array->data[0] = value;
    array->size++;
  } else {
    // Resize the array to accommodate the new element
    reset_arena(array->arena);
    char *newData = alloc_arena(array->arena, (array->size + 1) * sizeof(char));
    // Copy existing data to the new block
    for (int i = 0; i < array->size; i++) {
      newData[i] = array->data[i];
    }
    // Add the new value to the end
    newData[array->size] = value;
    // Update the array's data pointer and size
    // arena_reset(array->arena);  // Free the old memory
    array->data = newData;
    array->size++;
  }
}

void array_remove_by_index(Array *array, int index) {
  reset_arena(array->arena);
  char *newData = alloc_arena(array->arena, (array->size - 1) * sizeof(char));
  for (int i = 0; i < array->size; i++) {
    int new_index = i >= index ? i + 1 : i;
    newData[i] = array->data[new_index];
  }
  array->data = newData;
  array->size--;
}

void print_array(Array *array) {
  printf("[");
  for (int i = 0; i < array->size; i++) {
    printf("%d%c", array->data[i], i < array->size - 1 ? ',' : '\0');
  }
  printf("]\n");
}


// int main() {
//   Arena *arena = create_arena();
//   Array *array = arena_alloc(arena, sizeof(Array));
//   array->size = 0;
//   array->data = NULL;
//   array->arena = create_arena();

//   for (int i = 0; i < 10; i++) {
//     array_append(1 + i, array);
//   }

//   array_remove_by_index(array, 2);

//   print_array(array);
//   print_arena(array->arena);
//   // print_arena(arena);

//   destroy_arena(array->arena);
//   destroy_arena(arena);

//   printf("Bytes array: %ld\n", sizeof(Array));
//   printf("Bytes arena: %ld\n", sizeof(Arena));
//   return 0;
// }