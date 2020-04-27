/*****************************************************************************
*                                                                            *
*  -------------------------------- heap.h --------------------------------  *
*                                                                            *
*****************************************************************************/

#ifndef MAC_HEAP_H
#define MAC_HEAP_H

/*****************************************************************************
*                                                                            *
*  Define a structure for heaps.                                             *
*                                                                            *
*****************************************************************************/

typedef struct Heap_ {

int                size;

int                (*compare)(const void *key1, const void *key2);
void               (*destroy)(void *data);

void               **tree;

} Heap;

typedef Heap mac_heap_t;

/*****************************************************************************
*                                                                            *
*  --------------------------- Public Interface ---------------------------  *
*                                                                            *
*****************************************************************************/

void mac_heap_init(Heap *heap, int (*compare)(const void *key1, const void *key2),
   void (*destroy)(void *data));

void mac_heap_destroy(Heap *heap);

int mac_heap_insert(Heap *heap, const void *data);

int mac_heap_extract(Heap *heap, void **data);

#define mac_heap_size(heap) ((heap)->size)

#endif
