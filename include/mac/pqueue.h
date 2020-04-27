/*****************************************************************************
*                                                                            *
*  ------------------------------- pqueue.h -------------------------------  *
*                                                                            *
*****************************************************************************/

#ifndef PQUEUE_H
#define PQUEUE_H

#include "heap.h"

/*****************************************************************************
*                                                                            *
*  Implement priority queues as heaps.                                       *
*                                                                            *
*****************************************************************************/

typedef Heap PQueue;

/*****************************************************************************
*                                                                            *
*  --------------------------- Public Interface ---------------------------  *
*                                                                            *
*****************************************************************************/

#define pmac_queue_init mac_heap_init

#define pmac_queue_destroy mac_heap_destroy

#define pmac_queue_insert mac_heap_insert

#define pmac_queue_extract mac_heap_extract

#define pmac_queue_peek(pqueue) ((pqueue)->tree == NULL ? NULL : (pqueue)->tree[0])

#define pmac_queue_size mac_heap_size

#endif
