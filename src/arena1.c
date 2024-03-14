#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Arena {
    size_t size;
    size_t used;
    void* start;
} Arena;

Arena* arena_create(size_t size) {
    Arena* a = malloc(sizeof(Arena));
    a->size = size;
    a->used = 0;
    a->start = malloc(size);
    return a;
}

void* arena_alloc(Arena* a, size_t size) {
    if (a->used + size > a->size) {
        return NULL;
    }
    void* ptr = (char*)a->start + a->used;
    a->used += size;
    return ptr;
}

void arena_clear(Arena* a) {
    a->used = 0;
}

void arena_destroy(Arena* a) {
    free(a->start);
    free(a);
}

int main() {
    Arena* my_arena = arena_create(1024);
    if (my_arena == NULL) {
        printf("Failed to create arena\n");
        return 1;
    }

    int* int_ptr1 = arena_alloc(my_arena, sizeof(int));
    if (int_ptr1 == NULL) {
        printf("Failed to allocate memory in arena\n");
        return 1;
    }
    *int_ptr1 = 42;

    int* int_ptr2 = arena_alloc(my_arena, sizeof(int));
    if (int_ptr2 == NULL) {
        printf("Failed to allocate memory in arena\n");
        return 1;
    }
    *int_ptr2 = 13;

    printf("First integer: %d\n", *int_ptr1);
    printf("Second integer: %d\n", *int_ptr2);

    arena_clear(my_arena);
    arena_destroy(my_arena);

    return 0;
}