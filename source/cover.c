/*****************************************************************************
*                                                                            *
*  -------------------------------- cover.c -------------------------------  *
*                                                                            *
*****************************************************************************/

#include <stdlib.h>

#include "cover.h"
#include "list.h"
#include "set.h"

/*****************************************************************************
*                                                                            *
*  --------------------------------- cover --------------------------------  *
*                                                                            *
*****************************************************************************/

int cover(Set *members, Set *subsets, Set *covering) {

Set                intersection;

KSet               *subset;

ListElmt           *member,
                   *max_member;

void               *data;

int                max_size;

/*****************************************************************************
*                                                                            *
*  Initialize the covering.                                                  *
*                                                                            *
*****************************************************************************/

mac_set_init(covering, subsets->match, NULL);

/*****************************************************************************
*                                                                            *
*  Continue while there are noncovered members and candidate subsets.        *
*                                                                            *
*****************************************************************************/

while (mac_set_size(members) > 0 && mac_set_size(subsets) > 0) {

   /**************************************************************************
   *                                                                         *
   *  Find the subset that covers the most members.                          *
   *                                                                         *
   **************************************************************************/

   max_size = 0;

   for (member = mac_list_head(subsets); member != NULL; member =
      mac_list_next(member)) {

      if (mac_set_intersection(&intersection, &((KSet *)mac_list_data(member))->set,
         members) != 0) {

         return -1;

      }

      if (mac_set_size(&intersection) > max_size) {

         max_member = member;
         max_size = mac_set_size(&intersection);

      }

      mac_set_destroy(&intersection);

   }

   /**************************************************************************
   *                                                                         *
   *  A covering is not possible if there was no intersection.               *
   *                                                                         *
   **************************************************************************/

   if (max_size == 0)
      return 1;

   /**************************************************************************
   *                                                                         *
   *  Insert the selected subset into the covering.                          *
   *                                                                         *
   **************************************************************************/

   subset = (KSet *)mac_list_data(max_member);

   if (mac_set_insert(covering, subset) != 0) 
      return -1;

   /**************************************************************************
   *                                                                         *
   *  Remove each covered member from the set of noncovered members.         *
   *                                                                         *
   **************************************************************************/

   for (member = mac_list_head(&((KSet *)mac_list_data(max_member))->set); member !=
      NULL; member = mac_list_next(member)) {

      data = mac_list_data(member);

      if (mac_set_remove(members, (void**)&data) == 0 && members->destroy != NULL)
         members->destroy(data);

   }

   /**************************************************************************
   *                                                                         *
   *  Remove the subset from the set of candidate subsets.                   *
   *                                                                         *
   **************************************************************************/

   if (mac_set_remove(subsets, (void **)&subset) != 0)
      return -1;

}

/*****************************************************************************
*                                                                            *
*  No covering is possible if there are still noncovered members.            *
*                                                                            *
*****************************************************************************/

if (mac_set_size(members) > 0)
   return -1;

return 0;

}
