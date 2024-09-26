
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



