/*****************************************************************************
*                                                                            *
*  -------------------------------- set.c ---------------------------------  *
*                                                                            *
*****************************************************************************/

#include <stdlib.h>
#include <string.h>

#include "mac/list.h"
#include "mac/set.h"

/*****************************************************************************
*                                                                            *
*  ------------------------------- mac_set_init -------------------------------  *
*                                                                            *
*****************************************************************************/

void mac_set_init(Set *set, size_t el_size, int (*match)(const void *key1, const void *key2),
   void (*destroy)(void *data)) {

/*****************************************************************************
*                                                                            *
*  Initialize the set.                                                       *
*                                                                            *
*****************************************************************************/

mac_list_init(set, el_size, destroy);
set->match = match;

return;

}

/*****************************************************************************
*                                                                            *
*  ------------------------------ mac_set_insert ------------------------------  *
*                                                                            *
*****************************************************************************/

int mac_set_insert(Set *set, const void *data) {

/*****************************************************************************
*                                                                            *
*  Do not allow the insertion of duplicates.                                 *
*                                                                            *
*****************************************************************************/

if (mac_set_is_member(set, data))
   return 1;

/*****************************************************************************
*                                                                            *
*  Insert the data.                                                          *
*                                                                            *
*****************************************************************************/

return mac_list_ins_next(set, mac_list_tail(set), data);

}

/*****************************************************************************
*                                                                            *
*  ------------------------------ mac_set_remove ------------------------------  *
*                                                                            *
*****************************************************************************/

int mac_set_remove(Set *set, void **data) {

ListElmt           *member,
                   *prev;

/*****************************************************************************
*                                                                            *
*  Find the member to remove.                                                *
*                                                                            *
*****************************************************************************/

prev = NULL;

for (member = mac_list_head(set); member != NULL; member = mac_list_next(member)) {

   if (set->match(*data, mac_list_data(member)))
      break;

   prev = member;

}

/*****************************************************************************
*                                                                            *
*  Return if the member was not found.                                       *
*                                                                            *
*****************************************************************************/

if (member == NULL)
   return -1;

/*****************************************************************************
*                                                                            *
*  Remove the member.                                                        *
*                                                                            *
*****************************************************************************/

return mac_list_rem_next(set, prev, data);

}

/*****************************************************************************
*                                                                            *
*  ------------------------------- mac_set_union ------------------------------  *
*                                                                            *
*****************************************************************************/

int mac_set_union(Set *setu, const Set *set1, const Set *set2) {

ListElmt           *member;

void               *data;

/*****************************************************************************
*                                                                            *
*  Initialize the set for the union.                                         *
*                                                                            *
*****************************************************************************/

mac_set_init(setu, set1->el_size, set1->match, NULL);

/*****************************************************************************
*                                                                            *
*  Insert the members of the first set.                                      *
*                                                                            *
*****************************************************************************/

for (member = mac_list_head(set1); member != NULL; member = mac_list_next(member)) {

   data = mac_list_data(member);

   if (mac_list_ins_next(setu, mac_list_tail(setu), data) != 0) {

      mac_set_destroy(setu);
      return -1;

   }

}

/*****************************************************************************
*                                                                            *
*  Insert the members of the second set.                                     *
*                                                                            *
*****************************************************************************/

for (member = mac_list_head(set2); member != NULL; member = mac_list_next(member)) {

   if (mac_set_is_member(set1, mac_list_data(member))) {

      /***********************************************************************
      *                                                                      *
      *  Do not allow the insertion of duplicates.                           *
      *                                                                      *
      ***********************************************************************/

      continue;

      }

   else {

      data = mac_list_data(member);

      if (mac_list_ins_next(setu, mac_list_tail(setu), data) != 0) {

         mac_set_destroy(setu);
         return -1;

      }

   }

}

return 0;

}

/*****************************************************************************
*                                                                            *
*  --------------------------- mac_set_intersection ---------------------------  *
*                                                                            *
*****************************************************************************/

int mac_set_intersection(Set *seti, const Set *set1, const Set *set2) {

ListElmt           *member;

void               *data;

/*****************************************************************************
*                                                                            *
*  Initialize the set for the intersection.                                  *
*                                                                            *
*****************************************************************************/

mac_set_init(seti, set1->el_size, set1->match, NULL);

/*****************************************************************************
*                                                                            *
*  Insert the members present in both sets.                                  *
*                                                                            *
*****************************************************************************/

for (member = mac_list_head(set1); member != NULL; member = mac_list_next(member)) {

   if (mac_set_is_member(set2, mac_list_data(member))) {

      data = mac_list_data(member);

      if (mac_list_ins_next(seti, mac_list_tail(seti), data) != 0) {

         mac_set_destroy(seti);
         return -1;

      }

   }

}

return 0;

}

/*****************************************************************************
*                                                                            *
*  ---------------------------- mac_set_difference ----------------------------  *
*                                                                            *
*****************************************************************************/

int mac_set_difference(Set *setd, const Set *set1, const Set *set2) {

ListElmt           *member;

void               *data;

/*****************************************************************************
*                                                                            *
*  Initialize the set for the difference.                                    *
*                                                                            *
*****************************************************************************/

mac_set_init(setd, set1->el_size, set1->match, NULL);

/*****************************************************************************
*                                                                            *
*  Insert the members from set1 not in set2.                                 *
*                                                                            *
*****************************************************************************/

for (member = mac_list_head(set1); member != NULL; member = mac_list_next(member)) {

   if (!mac_set_is_member(set2, mac_list_data(member))) {

      data = mac_list_data(member);

      if (mac_list_ins_next(setd, mac_list_tail(setd), data) != 0) {

         mac_set_destroy(setd);
         return -1;

      }

   }

}

return 0;

}

/*****************************************************************************
*                                                                            *
*  ----------------------------- mac_set_is_member ----------------------------  *
*                                                                            *
*****************************************************************************/

int mac_set_is_member(const Set *set, const void *data) {

ListElmt           *member;

/*****************************************************************************
*                                                                            *
*  Determine if the data is a member of the set.                             *
*                                                                            *
*****************************************************************************/

for (member = mac_list_head(set); member != NULL; member = mac_list_next(member)) {

   if (set->match(data, mac_list_data(member)))
      return 1;

}

return 0;

}

/*****************************************************************************
*                                                                            *
*  ----------------------------- mac_set_is_subset ----------------------------  *
*                                                                            *
*****************************************************************************/

int mac_set_is_subset(const Set *set1, const Set *set2) {

ListElmt           *member;

/*****************************************************************************
*                                                                            *
*  Do a quick test to rule out some cases.                                   *
*                                                                            *
*****************************************************************************/

if (mac_set_size(set1) > mac_set_size(set2))
   return 0;

/*****************************************************************************
*                                                                            *
*  Determine if set1 is a subset of set2.                                    *
*                                                                            *
*****************************************************************************/

for (member = mac_list_head(set1); member != NULL; member = mac_list_next(member)) {

   if (!mac_set_is_member(set2, mac_list_data(member)))
      return 0;

}

return 1;

}

/*****************************************************************************
*                                                                            *
*  ------------------------------ mac_set_is_equal ----------------------------  *
*                                                                            *
*****************************************************************************/

int mac_set_is_equal(const Set *set1, const Set *set2) {

/*****************************************************************************
*                                                                            *
*  Do a quick test to rule out some cases.                                   *
*                                                                            *
*****************************************************************************/

if (mac_set_size(set1) != mac_set_size(set2))
   return 0;

/*****************************************************************************
*                                                                            *
*  Sets of the same size are equal if they are subsets.                      *
*                                                                            *
*****************************************************************************/

return mac_set_is_subset(set1, set2);

}
