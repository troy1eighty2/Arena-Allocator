#include "memalloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main( int argc, char * argv[] )
{
  clock_t start, end;
  double cpu_time_used;

  char *mallocfunction = "malloc";
  char *freefunction = "free";
  int numAllocations = 10000;
  int blockSize = 16;
  int** arrayOfPointers = NULL;

  
  start = clock();
  arrayOfPointers = malloc(numAllocations * blockSize);
  for (int i = 0; i < numAllocations; ++i){
    arrayOfPointers[i] = malloc(blockSize);

  }
  end = clock();

  cpu_time_used = ((double) (end - start) * 1000) / CLOCKS_PER_SEC;

  printf("\n");
  printf("Little Allocations/ Little Blocks-----------------------------------------------------------------\n");
  printf("Function: %s, Time taken: %f miliseconds for %d allocations with block size %d\n", mallocfunction, cpu_time_used, numAllocations, blockSize);
  printf("\n");

  start = clock();
  for (int i = 0; i < numAllocations; ++i){
    free(arrayOfPointers[i]);

  }
  free(arrayOfPointers);

  end = clock();
  cpu_time_used = ((double) (end - start) * 1000) / CLOCKS_PER_SEC;
  printf("Freeing Little Allocations/ Freeing Little Blocks-------------------------------------------------\n");
  printf("Function: %s, Time taken: %f miliseconds for %d allocations with block size %d\n", freefunction, cpu_time_used, numAllocations, blockSize);
  printf("\n");

  numAllocations = 100000;
  blockSize = 4096;

  start = clock();
  arrayOfPointers = malloc(numAllocations * blockSize);
  for (int i = 0; i < numAllocations; ++i){
    arrayOfPointers[i] = malloc(blockSize);

  }
  end = clock();
  cpu_time_used = ((double) (end - start) * 1000) / CLOCKS_PER_SEC;

  printf("Large Allocations/ Large Blocks-------------------------------------------------------------------\n");
  printf("Function: %s, Time taken: %f miliseconds for %d allocations with block size %d\n", mallocfunction, cpu_time_used, numAllocations, blockSize);
  printf("\n");

  start = clock();
  for (int i = 0; i < numAllocations; ++i){
    free(arrayOfPointers[i]);

  }
  free(arrayOfPointers);

  end = clock();
  cpu_time_used = ((double) (end - start) * 1000) / CLOCKS_PER_SEC;
  printf("Freeing Large Allocations/ Freeing Large Blocks---------------------------------------------------\n");
  printf("Function: %s, Time taken: %f miliseconds for %d allocations with block size %d\n", freefunction, cpu_time_used, numAllocations, blockSize);
  printf("\n");

  char *ptr = NULL;
  start = clock();
  for (int i = 0; i < 1000; i++){
    ptr = malloc(blockSize);
    free(ptr);

  }
  end = clock();
  cpu_time_used = ((double) (end - start) * 1000) / CLOCKS_PER_SEC;
  printf("Allocate, Free, Repeat 1000 times-------------------------------------------------------------------\n");
  printf("Function: %s, Time taken: %f miliseconds for 1000 allocations/frees with block size %d\n", freefunction, cpu_time_used, blockSize);
  printf("\n");

  return 0;
}
