#ifndef MY_MALLOC_H
#define MY_MALLOC_H

#include <stdio.h>
#include <sys/mman.h>
#include <stddef.h>
#include <stdbool.h>

/**
 * @brief Initializes the heap for the custom allocator.
 * 
 * Allocates a memory pool of `num_pages` using `mmap` system call. Each page is 4KB.
 * This serves as the heap for the custom memory allocator.
 * 
 * @param num_pages The number of 4KB pages to allocate for the heap.
 */
void initialize_memory(size_t num_pages);

/**
 * @brief Allocates memory from the custom heap.
 * 
 * Finds a free block in the heap to satisfy the requested size. Marks the block
 * as used and returns a pointer to the allocated memory. Returns NULL if no suitable
 * block is available.
 * 
 * @param size Number of bytes to allocate.
 * @return void* Pointer to the allocated memory or NULL if allocation fails.
 */
void *my_malloc(size_t size);

/**
 * @brief Frees a block of memory.
 * 
 * Marks the memory block as free and merges adjacent free blocks to prevent fragmentation.
 * 
 * @param ptr Pointer to memory block to be freed.
 */
void my_free(void *ptr);

#endif
