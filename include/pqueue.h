#ifndef PQUEUE_H
#define PQUEUE_H

#include "heap.h"

typedef Heap PQueue;

#define pqueue_init heap_init
#define pqueue_destroy heap_destroy
#define pqueue_insert heap_insert
#define pqueue_extract heap_extract
#define pqueue_peek( file_p ) ( (file_p)->arbre == NULL ? NULL : (file_p)->arbre[0] )
#define pqueue_size heap_size

#endif 