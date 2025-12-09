#ifndef JONALLOCATORS_ARENA_H
#define JONALLOCATORS_ARENA_H

#include <stddef.h>

typedef struct jonArena_s {
  void *data;
  void *offset;    // if offset == capacity , no allocations have been made
  size_t capacity; // capacity == 0 indicates deleted arena
} jonArena;

jonArena jon_arena_create(size_t size);
void jon_arena_delete(jonArena *const arena);
void *jon_arena_alloc(jonArena *const arena, size_t size);
void jon_arena_reset(jonArena *const arena);

#endif // JONALLOCATORS_ARENA_H
