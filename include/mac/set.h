/*****************************************************************************
*                                                                            *
*  -------------------------------- set.h ---------------------------------  *
*                                                                            *
*****************************************************************************/

#ifndef MAC_SET_H
#define MAC_SET_H

#include <stdlib.h>

#include "list.h"

/*****************************************************************************
*                                                                            *
*  Implement sets as linked lists.                                           *
*                                                                            *
*****************************************************************************/

typedef List Set;

/*****************************************************************************
*                                                                            *
*  --------------------------- Public Interface ---------------------------  *
*                                                                            *
*****************************************************************************/

void mac_set_init(Set *set, int (*match)(const void *key1, const void *key2),
   void (*destroy)(void *data));

#define mac_set_destroy mac_list_destroy

int mac_set_insert(Set *set, const void *data);

int mac_set_remove(Set *set, void **data);

int mac_set_union(Set *setu, const Set *set1, const Set *set2);

int mac_set_intersection(Set *seti, const Set *set1, const Set *set2);

int mac_set_difference(Set *setd, const Set *set1, const Set *set2);

int mac_set_is_member(const Set *set, const void *data);

int mac_set_is_subset(const Set *set1, const Set *set2);

int mac_set_is_equal(const Set *set1, const Set *set2);

#define mac_set_size(set) ((set)->size)

#endif
