#include "jonallocators/arena.h"
#include "jonallocators/memory_functions.h"
#include <assert.h>
#include <stdlib.h>

jonArena jon_arena_create(size_t size) {
  jonArena result = {.data = NULL, .offset = NULL, .capacity = 0};
  void *memory_block = jon_malloc(size);
  if (memory_block == NULL) {
    return result;
  }
  result.data = memory_block;
  result.offset = memory_block;
  result.capacity = size;

  return result;
}

void jon_arena_delete(jonArena *const arena) {
  assert(arena->capacity && arena->data);
  jon_free(arena->data);
  arena->data = NULL;
  arena->offset = NULL;
  arena->capacity = 0;
}

void *jon_arena_alloc(jonArena *const arena, size_t size) {
  void *result = NULL;
  const size_t used_capacity = (size_t)arena->offset - (size_t)arena->data;
  const size_t free_capacity = arena->capacity - used_capacity;
  if (size <= free_capacity) {
    result = arena->offset;
    arena->offset = (void *)((size_t)arena->offset + size);
  }
  return result;
}
