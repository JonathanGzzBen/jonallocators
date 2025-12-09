#include "jonallocators/arena.h"
#include <assert.h>
#include <stdlib.h>

jonArena jon_arena_create(size_t size) {
  jonArena result = {.data = NULL, .offset = NULL, .capacity = 0};
  void *memory_block = malloc(size);
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
  free(arena->data);
  arena->data = NULL;
  arena->offset = NULL;
  arena->capacity = 0;
}
