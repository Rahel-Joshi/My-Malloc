#include <stdio.h>
#include <sys/mman.h>
#include <stddef.h>
#include <stdbool.h>
#include "my_malloc.h"

const size_t PAGE_SIZE = 4096; // Size of each page (4KB)
const size_t PAGE_NUM = 16;

// Structure to represent each page/block
typedef struct page {
    size_t size;        // Size of the block (number of bytes)
    bool is_free;       // 1 if free, 0 if allocated
    struct page *next;  // Pointer to the next page/block in the free list
    struct page *prev;  // Pointer to the previous page/block
} page_t;

// Pointer to the start of the free list
page_t *head = NULL;

// Initialize the memory pool with mmap
void initialize_memory(size_t num_pages) {
    size_t num_bytes = num_pages * PAGE_SIZE;
    head = mmap(NULL, num_bytes, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    
    if (head == MAP_FAILED) {
        perror("mmap failed");
        return;
    }

    head->size = num_bytes - sizeof(page_t);
    head->is_free = true;
    head->next = NULL;
    head->prev = NULL;
}

// Find the first free block large enough to satisfy the request
page_t *find_free_block(size_t size) {
    page_t *curr = head;
    while (curr != NULL && (!curr->is_free || curr->size < size)) {
        curr = curr->next;
    }
    return curr;  // Return NULL if no suitable block is found
}

// Allocate memory by finding the first free block
void *my_malloc(size_t size) {
    page_t *curr = find_free_block(size);
    if (curr == NULL) return NULL;  // No free block found

    size_t size_diff = curr->size - size;
    page_t *next = curr->next;
    curr->is_free = false;

    if (next != NULL && next->is_free && size_diff > 0) {
        next->size += size_diff;
        curr->size -= size_diff;
    } else if (size_diff > sizeof(page_t)) {
        page_t *next2 = (page_t *)((char *)curr + sizeof(page_t) + size);
        next2->is_free = true;
        next2->prev = curr;
        next2->size = size_diff - sizeof(page_t);
        next2->next = NULL;

        if (next != NULL) {
            next->prev = next2;
            next2->next = next;
        }

        curr->size -= size_diff;
        curr->next = next2;
    }

    // Return pointer to usable memory after the metadata
    return (void *)(curr + 1);
}

// Free the allocated block and merge adjacent free blocks
void my_free(void *ptr) {
    page_t *curr = (page_t *)ptr - 1;
    curr->is_free = true;

    page_t *prev = curr->prev;
    page_t *next = curr->next;

    // Merge with the next block if it's free
    if (next != NULL && next->is_free) {
        page_t *next2 = next->next;
        curr->size += sizeof(page_t) + next->size;
        curr->next = next2;

        if (next2 != NULL) next2->prev = curr;
    }

    // Merge with the previous block if it's free
    if (prev != NULL && prev->is_free) {
        page_t *prev2 = prev->prev;
        prev->size += sizeof(page_t) + curr->size;
        prev->next = curr->next;

        if (curr->next != NULL) curr->next->prev = prev;
    }
}
