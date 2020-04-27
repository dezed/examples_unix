/*****************************************************************************
*                                                                            *
*  ------------------------------- queue.h --------------------------------  *
*                                                                            *
*****************************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

#include "list.h"

/*****************************************************************************
*                                                                            *
*  Implement queues as linked lists.                                         *
*                                                                            *
*****************************************************************************/

typedef List Queue;

typedef Queue mac_queue_t;

/*****************************************************************************
*                                                                            *
*  --------------------------- Public Interface ---------------------------  *
*                                                                            *
*****************************************************************************/

#define mac_queue_init mac_list_init

#define mac_queue_destroy mac_list_destroy

int mac_queue_enqueue(Queue *queue, const void *data);

int mac_queue_dequeue(Queue *queue, void **data);

#define mac_queue_peek(queue) ((queue)->head == NULL ? NULL : (queue)->head->data)

#define mac_queue_size mac_list_size

#endif
