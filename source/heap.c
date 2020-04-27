/*****************************************************************************
*                                                                            *
*  -------------------------------- heap.c --------------------------------  *
*                                                                            *
*****************************************************************************/

#include <stdlib.h>
#include <string.h>

#include "mac/heap.h"

/*****************************************************************************
*                                                                            *
*  Define private macros used by the heap implementation.                    *
*                                                                            *
*****************************************************************************/

#define mac_heap_parent(npos) ((int)(((npos) - 1) / 2))

#define mac_heap_left(npos) (((npos) * 2) + 1)

#define mac_heap_right(npos) (((npos) * 2) + 2)

/*****************************************************************************
*                                                                            *
*  ------------------------------- mac_heap_init ------------------------------  *
*                                                                            *
*****************************************************************************/

void mac_heap_init(Heap *heap, int (*compare)(const void *key1, const void *key2),
   void (*destroy)(void *data)) {

/*****************************************************************************
*                                                                            *
*  Initialize the heap.                                                      *
*                                                                            *
*****************************************************************************/

heap->size = 0;
heap->compare = compare;
heap->destroy = destroy;
heap->tree = NULL;

return;

}

/*****************************************************************************
*                                                                            *
*  ----------------------------- mac_heap_destroy -----------------------------  *
*                                                                            *
*****************************************************************************/

void mac_heap_destroy(Heap *heap) {

int                i;

/*****************************************************************************
*                                                                            *
*  Remove all the nodes from the heap.                                       *
*                                                                            *
*****************************************************************************/

if (heap->destroy != NULL) {

   for (i = 0; i < mac_heap_size(heap); i++) {

      /***********************************************************************
      *                                                                      *
      *  Call a user-defined function to free dynamically allocated data.    *
      *                                                                      *
      ***********************************************************************/

      heap->destroy(heap->tree[i]);

   }

}

/*****************************************************************************
*                                                                            *
*  Free the storage allocated for the heap.                                  *
*                                                                            *
*****************************************************************************/

free(heap->tree);

/*****************************************************************************
*                                                                            *
*  No operations are allowed now, but clear the structure as a precaution.   *
*                                                                            *
*****************************************************************************/

memset(heap, 0, sizeof(Heap));

return;

}

/*****************************************************************************
*                                                                            *
*  ------------------------------ mac_heap_insert -----------------------------  *
*                                                                            *
*****************************************************************************/

int mac_heap_insert(Heap *heap, const void *data) {

void               *temp;

int                ipos,
                   ppos;

/*****************************************************************************
*                                                                            *
*  Allocate storage for the node.                                            *
*                                                                            *
*****************************************************************************/

if ((temp = (void **)realloc(heap->tree, (mac_heap_size(heap) + 1) * sizeof
   (void *))) == NULL) {

   return -1;

   }

else {

   heap->tree = temp;

}

/*****************************************************************************
*                                                                            *
*  Insert the node after the last node.                                      *
*                                                                            *
*****************************************************************************/

heap->tree[mac_heap_size(heap)] = (void *)data;

/*****************************************************************************
*                                                                            *
*  Heapify the tree by pushing the contents of the new node upward.          *
*                                                                            *
*****************************************************************************/

ipos = mac_heap_size(heap);
ppos = mac_heap_parent(ipos);

while (ipos > 0 && heap->compare(heap->tree[ppos], heap->tree[ipos]) < 0) {

   /**************************************************************************
   *                                                                         *
   *  Swap the contents of the current node and its parent.                  *
   *                                                                         *
   **************************************************************************/

   temp = heap->tree[ppos];
   heap->tree[ppos] = heap->tree[ipos];
   heap->tree[ipos] = temp;

   /**************************************************************************
   *                                                                         *
   *  Move up one level in the tree to continue heapifying.                  *
   *                                                                         *
   **************************************************************************/

   ipos = ppos;
   ppos = mac_heap_parent(ipos);

}

/*****************************************************************************
*                                                                            *
*  Adjust the size of the heap to account for the inserted node.             *
*                                                                            *
*****************************************************************************/

heap->size++;

return 0;

}

/*****************************************************************************
*                                                                            *
*  ----------------------------- mac_heap_extract -----------------------------  *
*                                                                            *
*****************************************************************************/

int mac_heap_extract(Heap *heap, void **data) {

void               *save,
                   *temp;

int                ipos,
                   lpos,
                   rpos,
                   mpos;

/*****************************************************************************
*                                                                            *
*  Do not allow extraction from an empty heap.                               *
*                                                                            *
*****************************************************************************/

if (mac_heap_size(heap) == 0)
   return -1;

/*****************************************************************************
*                                                                            *
*  Extract the node at the top of the heap.                                  *
*                                                                            *
*****************************************************************************/

*data = heap->tree[0];

/*****************************************************************************
*                                                                            *
*  Adjust the storage used by the heap.                                      *
*                                                                            *
*****************************************************************************/

save = heap->tree[mac_heap_size(heap) - 1];

if (mac_heap_size(heap) - 1 > 0) {

   if ((temp = (void **)realloc(heap->tree, (mac_heap_size(heap) - 1) * sizeof
      (void *))) == NULL) {

      return -1;

      }

   else {

      heap->tree = temp;

   }

   /**************************************************************************
   *                                                                         *
   *  Adjust the size of the heap to account for the extracted node.         *
   *                                                                         *
   **************************************************************************/

   heap->size--;

   }

else {

   /**************************************************************************
   *                                                                         *
   *  Manage the heap when extracting the last node.                         *
   *                                                                         *
   **************************************************************************/

   free(heap->tree);
   heap->tree = NULL;
   heap->size = 0;
   return 0;

}

/*****************************************************************************
*                                                                            *
*  Copy the last node to the top.                                            *
*                                                                            *
*****************************************************************************/

heap->tree[0] = save;

/*****************************************************************************
*                                                                            *
*  Heapify the tree by pushing the contents of the new top downward.         *
*                                                                            *
*****************************************************************************/

ipos = 0;
lpos = mac_heap_left(ipos);
rpos = mac_heap_right(ipos);

while (1) {

   /**************************************************************************
   *                                                                         *
   *  Select the child to swap with the current node.                        *
   *                                                                         *
   **************************************************************************/

   lpos = mac_heap_left(ipos);
   rpos = mac_heap_right(ipos);

   if (lpos < mac_heap_size(heap) && heap->compare(heap->tree[lpos], heap->
      tree[ipos]) > 0) {

      mpos = lpos;

      }

   else {

      mpos = ipos;

   }

   if (rpos < mac_heap_size(heap) && heap->compare(heap->tree[rpos], heap->
      tree[mpos]) > 0) {

      mpos = rpos;

   }

   /**************************************************************************
   *                                                                         *
   *  When mpos is ipos, the heap property has been restored.                *
   *                                                                         *
   **************************************************************************/

   if (mpos == ipos) {

      break;

      }

   else {

      /***********************************************************************
      *                                                                      *
      *  Swap the contents of the current node and the selected child.       *
      *                                                                      *
      ***********************************************************************/

      temp = heap->tree[mpos];
      heap->tree[mpos] = heap->tree[ipos];
      heap->tree[ipos] = temp;

      /***********************************************************************
      *                                                                      *
      *  Move down one level in the tree to continue heapifying.             *
      *                                                                      *
      ***********************************************************************/

      ipos = mpos;

   }

}

return 0;

}
