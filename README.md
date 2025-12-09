# jonallocators
Custom allocators written by me, Jonark

## About

### Arena Allocator

A simple arena, also called linear or bump allocator that preallocates a block of memory,
keeps track of an offset into it to distribute smaller blocks, but can only deallocate all
at once.
