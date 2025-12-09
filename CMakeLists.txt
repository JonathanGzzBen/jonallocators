cmake_minimum_required(VERSION 3.11)

project(jonallocators LANGUAGES C)

add_library(jonallocators_lib src/arena.c)
target_include_directories(jonallocators_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(jonallocators_test tests/tests.c)
target_link_libraries(jonallocators_test PRIVATE jonallocators_lib)
