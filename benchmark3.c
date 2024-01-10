#include "memalloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main( int argc, char * argv[] )
{
  clock_t start, end;
  double cpu_time_used;

  char *mallocfunction = "memalloc_alloc";
  char *freefunction = "memalloc_free";
  int numAllocations = 10000;
  int blockSize = 16;
  int arrayOfPointers = 0;
  void *ptr[numAllocations];

  
  start = clock();
  arrayOfPointers = memalloc_init(numAllocations * blockSize, WORST_FIT);
  for (int i = 0; i < numAllocations; ++i){
    ptr[i] = memalloc_alloc(blockSize);

  }
  end = clock();

  cpu_time_used = ((double) (end - start) * 1000) / CLOCKS_PER_SEC;

  printf("\n");
  printf("Little Allocations/ Little Blocks-----------------------------------------------------------------\n");
  printf("Function: %s, Time taken: %f miliseconds for %d allocations with block size %d\n", mallocfunction, cpu_time_used, numAllocations, blockSize);
  printf("\n");

  start = clock();
  for (int i = 0; i < numAllocations; ++i){
    memalloc_free(ptr[i]);

  }
  memalloc_destroy(arrayOfPointers);

  end = clock();
  cpu_time_used = ((double) (end - start) * 1000) / CLOCKS_PER_SEC;
  printf("Freeing Little Allocations/ Freeing Little Blocks-------------------------------------------------\n");
  printf("Function: %s, Time taken: %f miliseconds for %d allocations with block size %d\n", freefunction, cpu_time_used, numAllocations, blockSize);
  printf("\n");

  numAllocations = 100000;
  blockSize = 4096;
  void *ptr2[numAllocations];

  start = clock();
  arrayOfPointers = memalloc_init(numAllocations * blockSize, WORST_FIT);
  for (int i = 0; i < numAllocations; ++i){
    memalloc_alloc(blockSize);

  }
  end = clock();
  cpu_time_used = ((double) (end - start) * 1000) / CLOCKS_PER_SEC;

  printf("Large Allocations/ Large Blocks-------------------------------------------------------------------\n");
  printf("Function: %s, Time taken: %f miliseconds for %d allocations with block size %d\n", mallocfunction, cpu_time_used, numAllocations, blockSize);
  printf("\n");

  start = clock();
  for (int i = 0; i < numAllocations; ++i){
    memalloc_free(ptr2[i]);

  }
  memalloc_destroy(arrayOfPointers);
  end = clock();

  cpu_time_used = ((double) (end - start) * 1000) / CLOCKS_PER_SEC;
  printf("Freeing Large Allocations/ Freeing Large Blocks---------------------------------------------------\n");
  printf("Function: %s, Time taken: %f miliseconds for %d allocations with block size %d\n", freefunction, cpu_time_used, numAllocations, blockSize);
  printf("\n");

  void *ptrs = NULL;
  arrayOfPointers = memalloc_init(blockSize * 10, WORST_FIT);
  start = clock();
  for (int i = 0; i < 1000; i++){
    ptrs = memalloc_alloc(blockSize);
    memalloc_free(ptrs);

  }
  end = clock();
  memalloc_destroy(arrayOfPointers);
  cpu_time_used = ((double) (end - start) * 1000) / CLOCKS_PER_SEC;
  printf("Allocate, Free, Repeat 1000 times-------------------------------------------------------------------\n");
  printf("Function: %s, Time taken: %f miliseconds for 1000 allocations/frees with block size %d\n", freefunction, cpu_time_used, blockSize);
  printf("\n");

  return 0;
}