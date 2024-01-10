// The MIT License (MIT)
// 
// Copyright (c) 2021, 2022, 2023 Trevor Bakker 
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software. (RmFsbCAyMDIz)
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES UTA OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <limits.h>
#include "memalloc.h"

// pointer to pool of memory
void *pool;
enum ALGORITHM algo;
struct Node *LL;
// track alloc for NEXT_FIT
struct Node *track_alloc = NULL;

int memalloc_init( size_t size, enum ALGORITHM algorithm )
{
  // align the requested size and the size of a Node
  size_t alignedSize = ALIGN4(size);
  size_t alignedStructNode = ALIGN4(sizeof(struct Node));

  // if asking to allocate negative number of bytes, reject
  if (alignedSize < 0){
    return -1;
  }

  // set first LL Node
  pool = malloc(alignedSize);
  LL = (struct Node *)malloc(alignedStructNode);
  algo = algorithm;

  LL->size = alignedSize;
  LL->type = H;
  LL->arena = pool;
  LL->next = NULL;
  LL->previous = NULL;

  return 0;
}

void memalloc_destroy( )
{
  // free each Node of the LL and then free pool of mem
  struct Node * curr;
  while(LL){
    curr = LL;
    LL = LL->next;
    free(curr);
  }
  free(pool);
  return;
}

void * memalloc_alloc( size_t size )
{
  
  size_t alignedSize = ALIGN4(size);
  size_t alignedStructNode = ALIGN4(sizeof(struct Node));
  // create tmp pointer to iterate thru LL
  struct Node *tmp = LL;
  
  // conditional to do algorithm
  if (algo == FIRST_FIT){
    // while still in a Node in LL
    while(tmp){
      // if a candidate for allocating memory
      if (tmp->type == H && tmp->size >= alignedSize) {
        // if size of curr strictly larger than requested size, split the node; one for the requested size, one for the remainder
        if (tmp->size > alignedSize){
          struct Node * nn = (struct Node *)malloc(alignedStructNode);


          nn->arena = (tmp->arena) + tmp->size - alignedSize;
          nn->size = tmp->size - alignedSize;
          nn->type = H;

          nn->next = NULL;
          tmp->next = nn;
          nn->previous = tmp;

          
        }
        // if strictly request size == Node size, simply change the type of Node and set size
        tmp->type = P;
        tmp->size = alignedSize;
        return tmp->arena;
      }
      // increment LL
      tmp = tmp->next;
    }
    return NULL;
  }
  else if (algo == BEST_FIT){
    // capture smallest sized Node so far
    struct Node * small = NULL;
    // value to track whether or not this is the first candidate Node found
    int first = 1;

    // iterate thru the LL, small = min(small, curr->size)
    while (tmp){
      
      if (tmp->type == H && tmp->size >= alignedSize && first == 1) {
        small = tmp;
        first = 0;
      }
      else if (tmp->type == H && tmp->size >= alignedSize && tmp->size < small->size && first == 0){
        small = tmp;
      }
      tmp = tmp->next;
    }
    // if the first candidate Node hasnt been found, that means there are no Nodes that can accomodate for the requested alloc size, return NULL
    if (first == 1){
      return NULL;
    }
    // allocate newnode same as FIRST_FIT
    if (small->size >= alignedSize) {
      if (small->size > alignedSize){
        struct Node * nn = (struct Node *)malloc(alignedStructNode);

        nn->arena = (small->arena) + small->size - alignedSize;
        nn->size = small->size - alignedSize;
        nn->type = H;

        nn->next = NULL;
        small->next = nn;
        nn->previous = small;

      }

      small->type = P;
      small->size = alignedSize;
      return small->arena;

    }
    return NULL;
  }
  // same as BEST_FIT, with a flipped inequality operator to capture the largest sized candidate Node
  // got too lazy to change var name from small to large xD
  else if (algo == WORST_FIT){
    struct Node * small = NULL;
    int first = 1;

    // iterate thru the LL, small = max(small, curr->size)
    while (tmp){
      if (tmp->type == H && tmp->size >= alignedSize && first == 1) {
        small = tmp;
        first = 0;
      }
      else if (tmp->type == H && tmp->size >= alignedSize && tmp->size > small->size && first == 0){
        small = tmp;
      }
      tmp = tmp->next;
    }
    if (first == 1){
      return NULL;
    }
    if (small->size >= alignedSize) {
      if (small->size > alignedSize){
        struct Node * nn = (struct Node *)malloc(alignedStructNode);

        nn->arena = (small->arena) + small->size - alignedSize;
        nn->size = small->size - alignedSize;
        nn->type = H;

        nn->next = NULL;
        small->next = nn;
        nn->previous = small;

      }

      small->type = P;
      small->size = alignedSize;
      return small->arena;

    }
    return NULL;
  }
  else if (algo == NEXT_FIT){
    // if there is no Node left over from previous runs, set track_alloc to the head of LL
    if(!track_alloc){
      track_alloc = LL;
    }
    // same Node processing as the other algorithms
    tmp = track_alloc;
    while(tmp){
      if (tmp->type == H && tmp->size >= alignedSize) {
        if (tmp->size > alignedSize){
          
          struct Node * nn = (struct Node *)malloc(alignedStructNode);

          nn->arena = (tmp->arena) + tmp->size - alignedSize;
          nn->size = tmp->size - alignedSize;
          nn->type = H;

          nn->next = tmp->next;
          tmp->next = nn;
          nn->previous = tmp;

          
        }
        tmp->type = P;
        tmp->size = alignedSize;

        // set track_alloc to last Node processed
        track_alloc = tmp;
        return tmp->arena;
      }
      

      tmp = tmp->next;

      // put iterating pointer back on the head
      if(tmp == NULL){
        tmp = LL;
      }
      
      // end the searching if tmp is back to track_alloc
      if(tmp == track_alloc){
        break;
      }
    }
    track_alloc = tmp;
    return NULL;
  }
  return NULL;
}

void memalloc_free( void * ptr )
{
  struct Node * tmp = LL;
  // iterate thu LL searching for the requested Node to be freed
  while(tmp){
    if (ptr == tmp->arena){
      tmp->type = H;
      break;
    }
    tmp = tmp->next;
  }
  // if two adjacent Nodes are holes, combine the Nodes and set the pointers to next Node
  tmp = LL;
  while(tmp && tmp->next){
    if (tmp->type == H && tmp->next->type == H){
      tmp->size = tmp->size + tmp->next->size;
      tmp->next = tmp->next->next;

      continue;
    }
    tmp = tmp->next;
  }
  return;
}

int memalloc_size( )
{
  // iterate thru LL, incrementing a counter
  int number_of_nodes = 0;
  struct Node* tmp = LL;
  while(tmp){
    number_of_nodes++;
    tmp = tmp->next;
  }
  return number_of_nodes;
}

// RmFsbCAyMDIz-76f3-90d6-0703ac120003
