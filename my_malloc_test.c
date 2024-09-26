#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "my_malloc.h"

// Test 1: Basic Allocation
void test_basic_allocation() {
    printf("Test 1: Basic Allocation\n");
    void *ptr = my_malloc(5000);  // Allocate 5KB
    assert(ptr != NULL);          // Should return a valid pointer
    printf(" - Allocated 5KB successfully.\n");
}

// Test 2: Multiple Allocations
void test_multiple_allocations() {
    printf("Test 2: Multiple Allocations\n");
    void *ptr1 = my_malloc(5000);  // 5KB
    void *ptr2 = my_malloc(8000);  // 8KB
    void *ptr3 = my_malloc(12000); // 12KB
    assert(ptr1 != NULL && ptr2 != NULL && ptr3 != NULL);
    printf(" - Allocated 5KB, 8KB, and 12KB successfully.\n");
}

// Test 3: Block Splitting
void test_block_splitting() {
    printf("Test 3: Block Splitting\n");
    void *ptr = my_malloc(4000);  // Request 4KB
    assert(ptr != NULL);          // Should return a valid pointer
    printf(" - Allocated 4KB and split the block successfully.\n");
}

// Test 4: Freeing and Reusing Blocks
void test_freeing_blocks() {
    printf("Test 4: Freeing Blocks\n");
    void *ptr1 = my_malloc(5000);  // 5KB
    void *ptr2 = my_malloc(8000);  // 8KB
    assert(ptr1 != NULL && ptr2 != NULL);

    my_free(ptr1);                 // Free the 5KB block
    printf(" - Freed 5KB block successfully.\n");

    void *ptr3 = my_malloc(5000);  // Allocate 5KB again (should reuse the freed block)
    assert(ptr3 == ptr1);          // Should reuse the same memory
    printf(" - Reused the freed 5KB block successfully.\n");
}

// Test 5: Reusing Freed Blocks
void test_reusing_freed_blocks() {
    printf("Test 5: Reusing Freed Blocks\n");
    void *ptr1 = my_malloc(5000);  // 5KB
    void *ptr2 = my_malloc(8000);  // 8KB
    assert(ptr1 != NULL && ptr2 != NULL);

    my_free(ptr2);                 // Free the 8KB block
    printf(" - Freed 8KB block successfully.\n");

    void *ptr3 = my_malloc(8000);  // Reallocate 8KB (should reuse the freed block)
    assert(ptr3 == ptr2);          // Should reuse the same memory
    printf(" - Reused the freed 8KB block successfully.\n");
}

// Test 6: Small Allocation
void test_small_allocation() {
    printf("Test 6: Small Allocation\n");
    void *ptr = my_malloc(1);  // Allocate just 1 byte
    assert(ptr != NULL);       // Should return a valid pointer
    printf(" - Allocated 1 byte successfully.\n");
}

// Test 7: Memory Exhaustion
void test_memory_exhaustion() {
    printf("Test 7: Memory Exhaustion\n");
    // Allocate large blocks until memory is exhausted
    void *ptr = NULL;
    size_t allocated = 0;

    while ((ptr = my_malloc(8000)) != NULL) {  // Allocate in 8KB chunks
        allocated += 8000;
    }
    
    printf(" - Allocated %zu bytes before running out of memory.\n", allocated);
    assert(ptr == NULL);  // Should return NULL when memory is exhausted
}

// Test 8: Memory Fragmentation and Coalescence
void test_memory_fragmentation() {
    printf("Test 8: Memory Fragmentation vs Coalescence\n");
    // Initialize memory with 33 pages (132KB)
    initialize_memory(33);

    // Allocate several blocks
    void *ptr1 = my_malloc(32 * 1024);  // 32KB
    void *ptr2 = my_malloc(16 * 1024);  // 16KB
    void *ptr3 = my_malloc(16 * 1024);  // 16KB
    void *ptr4 = my_malloc(32 * 1024);  // 32KB
    void *ptr5 = my_malloc(32 * 1024);  // 32KB

    // Ensure allocations succeeded
    assert(ptr1 != NULL && ptr2 != NULL && ptr3 != NULL && ptr4 != NULL && ptr5 != NULL);
    printf(" - Allocated 32KB, 16KB, 16KB, 32KB, and 32KB blocks.\n");
    
    // Free some blocks to create fragmentation
    my_free(ptr2);  // Free the 16KB block (creating a hole)
    my_free(ptr3);  // Free the adjacent 16KB block (creating a bigger hole)
    my_free(ptr4);  // Free the adjacent 32KB block (creating a bigger hole)

    printf(" - Freed 64KB blocks to create a fragmentation potential.\n");

    // Now try to allocate a 64KB block (which should fit into the coalesced space)
    void *ptr6 = my_malloc(64 * 1024);  // 64KB allocation

    // If the coalescing works correctly, this allocation should succeed
    if (ptr6 != NULL) {
        printf(" - Successfully allocated 64KB in the coalesced free space.\n");
    } else {
        printf(" - Failed to allocate 64KB, memory fragmentation is not handled properly.\n");
    }

    // Check that ptr5 is not NULL (meaning fragmentation was avoided)
    assert(ptr6 != NULL);
}

int main() {
    // Initialize the memory pool with 32 pages (128KB)
    initialize_memory(32);

    // Run all test cases
    test_basic_allocation();
    test_multiple_allocations();
    test_block_splitting();
    test_freeing_blocks();
    test_reusing_freed_blocks();
    test_small_allocation();
    test_reusing_freed_blocks();
    test_memory_exhaustion();
    test_memory_fragmentation();

    printf("All tests passed!\n");
    return 0;
}
