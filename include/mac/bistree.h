/*****************************************************************************
*                                                                            *
*  ------------------------------- bistree.h ------------------------------  *
*                                                                            *
*****************************************************************************/

#ifndef BISTREE_H
#define BISTREE_H

#include "bitree.h"

/*****************************************************************************
*                                                                            *
*  Define balance factors for AVL trees.                                     *
*                                                                            *
*****************************************************************************/

#define            AVL_LFT_HEAVY         1
#define            AVL_BALANCED          0
#define            AVL_RGT_HEAVY        -1

/*****************************************************************************
*                                                                            *
*  Define a structure for nodes in AVL trees.                                *
*                                                                            *
*****************************************************************************/

typedef struct AvlNode_ {

void               *data;
int                hidden;
int                factor;

} AvlNode;

/*****************************************************************************
*                                                                            *
*  Implement binary search trees as binary trees.                            *
*                                                                            *
*****************************************************************************/

typedef BiTree BisTree;

typedef BisTree mac_bistree_t;

/*****************************************************************************
*                                                                            *
*  --------------------------- Public Interface ---------------------------  *
*                                                                            *
*****************************************************************************/

void mac_bistree_init(BisTree *tree, int (*compare)(const void *key1, const void
   *key2), void (*destroy)(void *data));

void mac_bistree_destroy(BisTree *tree);

int mac_bistree_insert(BisTree *tree, const void *data);

int mac_bistree_remove(BisTree *tree, const void *data);

int mac_bistree_lookup(BisTree *tree, void **data);

#define mac_bistree_size(tree) ((tree)->size)

#endif
