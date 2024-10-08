
# My-Malloc: Custom Memory Allocator API in C

This project implements a custom memory allocator in C using mmap system calls. It includes custom versions of malloc and free with optimization through a segregated free list strategy, which improves allocation efficiency and reduces fragmentation.




## Features

- **Custom malloc & free:** Implements memory allocation and freeing functions using mmap for dynamic memory management.

- **Segregated Free List:** Optimizes allocation by grouping free blocks into different size classes, allowing for fast allocation of memory and better reuse of blocks.

- **Efficient Memory Management:** Coalesces adjacent free blocks to reduce fragmentation.



## Files

- `my_malloc.c`: Contains the implementation of `my_malloc` and `my_free`.
- `my_malloc.h`: Header file declaring the custom allocation and freeing functions.
- `my_malloc_test.c`: Test suite that checks the functionality of the custom allocator.


## How to Build and Run Tests

**Compilation**

To compile the project and run the tests, use the following commands:

```
clang my_malloc_test.c my_malloc.c -o test
```
Or, if using gcc:

```
gcc my_malloc_test.c my_malloc.c -o test
```

**Running Tests**

Once the project is compiled, you can run the test cases using:

```
./test
```

This will execute a series of tests to ensure that the custom allocator is working correctly, including tests for memory allocation, freeing, and fragmentation handling.


**How to Use**

Look in `my_malloc.h` to see the available API calls :)

`initialize_memory(size_t num_pages)` initializes the heap with `num_pages` (each page starts off with 4096 bytes)

`my_malloc(size_t size)` returns a pointer to a chunk of heap memory with `size` bytes available

`my_free(void *ptr)` takes a `ptr` to an instance in heap memory and frees that chunk of heap memory

