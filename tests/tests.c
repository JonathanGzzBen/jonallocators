#include "jonallocators/arena.h"
#include <stdbool.h>
#include <stdio.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
// #define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
// #define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

void test_condition(const char *const condition_description, bool condition);

void test_condition(const char *const condition_description, bool condition) {
  printf(ANSI_COLOR_YELLOW "TESTING " ANSI_COLOR_RESET "%s: ",
         condition_description);
  if (condition)
    printf(ANSI_COLOR_GREEN "PASSED\n" ANSI_COLOR_RESET);
  else {
    printf(ANSI_COLOR_RED "FAILED\n" ANSI_COLOR_RESET);
  }
}

int main(void) {
  puts("jonallocators tests");

  puts(ANSI_COLOR_MAGENTA "  arena tests" ANSI_COLOR_RESET); // 2 spaces

  jonArena arena;
  void *allocated1;
  void *allocated2;

  arena = jon_arena_create(500);
  test_condition("Can create an arena with capacity",
                 arena.data != NULL && arena.offset != NULL &&
                     arena.capacity != 0);

  jon_arena_delete(&arena);
  test_condition("Can delete a valid arena with capacity",
                 arena.data == NULL && arena.offset == NULL &&
                     arena.capacity == 0);

  arena = jon_arena_create(10);

  allocated1 = jon_arena_alloc(&arena, 11);
  test_condition("alloc that surpasses capacity fails", allocated1 == NULL);

  allocated1 = jon_arena_alloc(&arena, 1);
  test_condition("alloc with enough capacity succeeds", allocated1 != NULL);

  allocated2 = jon_arena_alloc(&arena, 1);
  test_condition("Two consecutive allocs return contiguous addresses",
                 (size_t)allocated1 + 1 == (size_t)allocated2);

  allocated1 = jon_arena_alloc(&arena, 8);
  test_condition("Can entirely exhaust preallocated memory",
                 allocated1 != NULL);

  allocated1 = jon_arena_alloc(&arena, 1);
  test_condition("alloc on exhausted arena fails", allocated1 == NULL);

  jon_arena_delete(&arena);
  return 0;
}
