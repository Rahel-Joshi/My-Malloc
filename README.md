My-Malloc: Custom Memory Allocator in C
This project implements a custom memory allocator in C using mmap system calls. It includes custom versions of malloc and free with optimization through a segregated free list strategy, which improves allocation efficiency and reduces fragmentation.

Features
Custom malloc & free: Implements memory allocation and freeing functions using mmap for dynamic memory management.
Segregated Free List: Optimizes allocation by grouping free blocks into different size classes, allowing for fast allocation of memory and better reuse of blocks.
Efficient Memory Management: Coalesces adjacent free blocks to reduce fragmentation.
Files
my_malloc.c: Contains the implementation of my_malloc and my_free.
my_malloc.h: Header file declaring the custom allocation and freeing functions.
my_malloc_test.c: Test suite that checks the functionality of the custom allocator.
How to Build and Run Tests
Prerequisites
Ensure you have clang or gcc installed on your system.
Compilation
To compile the project and run the tests, use the following commands:

bash
Copy code
clang my_malloc_test.c my_malloc.c -o test
Or, if using gcc:

bash
Copy code
gcc my_malloc_test.c my_malloc.c -o test
Running Tests
Once the project is compiled, you can run the test cases using:

bash
Copy code
./test
This will execute a series of tests to ensure that the custom allocator is working correctly, including tests for memory allocation, freeing, and fragmentation handling.

Future Improvements
Implement better handling of larger memory requests.
Optimize memory coalescing for heavily fragmented memory pools.
Add support for more complex memory alignment strategies.