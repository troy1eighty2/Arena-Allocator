## Vision
This is a research project exploring the intricacies of malloc, a fundamental function in dynamic memory management. This endeavor seeks to investigate various memory management algorithms, comparing their effectiveness. Malloc plays a important role in enabling programmers to optimize system efficiency and performance by granting control over memory allocation. Within this project, we will assess the performance of custom malloc implementations utilizing first, best, worst, and next fit algorithms, offering insights into their comparative strengths and weaknesses.
## Methodology
* Report: https://docs.google.com/document/d/1qjEKr73p4x18M7808es3QQRPJS9jiznKvuJ5vo8Vuss/edit?usp=sharing
Initial pool of memory
* The initial pool of memory is the only time malloc is used.
Implementation of the memory allocator API
```
int memalloc_init( size_t size, enum ALGORITHM algorithm )
```
* This function will use malloc to allocate a pool of memory that is size bytes big. If the size parameter is less than zero then return -1. If allocation fails return -1.
```
void *memalloc_alloc( size_t size )
```
* This function will allocate size bytes from the preallocated memory pool using heap allocation algorithm during memalloc_init.
```
void memalloc_free( void * pointer )
```
* This function will free the allocated arena and empty the linked list.
Implementation of BEST_FIT, WORST_FIT, NEXT_FIT, FIRST_FIT
* The algorithm being used is specified as an enum that is a secondary parameter when creating the initial pool of memory with memalloc_init.
```
enum ALGORITHM
{
  NEXT_FIT = 0,
  BEST_FIT,
  WORST_FIT,
  FIRST_FIT
}; 
```
## Unit Testing
To ensure the program works as intended, all code is built with provided makefiles and unit tests.
## Benchmarking and Report
Benchmarks are conducted to assess the time complexity of both the standard malloc function and custom implementations. Clock times are recorded using the clock_t data type to mark the start and end times. 

In total, five timed tests are conducted. The initial test involvs initializing a block of memory and performing a malloc operation for each block. This process repeats twice for each malloc implementation: once with a small number of allocations and small memory blocks, and again with a large number of allocations and large memory blocks. Additionally, two free tests are carried out—one with large chunks and another with small chunks. Finally, the last test involvs allocating and freeing a single block of memory 1,000 times.

The results are documented in a spreadsheet, and the collected data is utilized to create a bar graph, visually representing the outcomes of the tests.
  
## Acknowledgements
Created at UT Arlington for 3320 Operating Systems taught by Professor Trevor Bakker. 
