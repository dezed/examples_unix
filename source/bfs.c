/*****************************************************************************
*                                                                            *
*  -------------------------------- bfs.c ---------------------------------  *
*                                                                            *
*****************************************************************************/

#include <stdlib.h>

#include "bfs.h"
#include "graph.h"
#include "list.h"
#include "queue.h"

/*****************************************************************************
*                                                                            *
*  --------------------------------- bfs ----------------------------------  *
*                                                                            *
*****************************************************************************/

int bfs(Graph *graph, BfsVertex *start, List *hops) {

Queue              queue;

AdjList            *adjlist,
                   *clr_adjlist;

BfsVertex          *clr_vertex,
                   *adj_vertex;

ListElmt           *element,
                   *member;

/*****************************************************************************
*                                                                            *
*  Initialize all of the vertices in the graph.                              *
*                                                                            *
*****************************************************************************/

for (element = mac_list_head(&graph_adjlists(graph)); element != NULL; element =
   mac_list_next(element)) {

   clr_vertex = ((AdjList *)mac_list_data(element))->vertex;

   if (graph->match(clr_vertex, start)) {

      /***********************************************************************
      *                                                                      *
      *  Initialize the start vertex.                                        *
      *                                                                      *
      ***********************************************************************/

      clr_vertex->color = gray;
      clr_vertex->hops = 0;

      }

   else {

      /***********************************************************************
      *                                                                      *
      *  Initialize vertices other than the start vertex.                    *
      *                                                                      *
      ***********************************************************************/

      clr_vertex->color = white;
      clr_vertex->hops = -1;

   }

}

/*****************************************************************************
*                                                                            *
*  Initialize the queue with the adjacency list of the start vertex.         *
*                                                                            *
*****************************************************************************/

mac_queue_init(&queue, NULL);

if (graph_adjlist(graph, start, &clr_adjlist) != 0) {

   mac_queue_destroy(&queue);
   return -1;

}

if (mac_queue_enqueue(&queue, clr_adjlist) != 0) {

   mac_queue_destroy(&queue);
   return -1;

}

/*****************************************************************************
*                                                                            *
*  Perform breadth-first search.                                             *
*                                                                            *
*****************************************************************************/

while (mac_queue_size(&queue) > 0) {

   adjlist = mac_queue_peek(&queue);

   /**************************************************************************
   *                                                                         *
   *  Traverse each vertex in the current adjacency list.                    *
   *                                                                         *
   **************************************************************************/

   for (member = mac_list_head(&adjlist->adjacent); member != NULL; member =
      mac_list_next(member)) {

      adj_vertex = mac_list_data(member);

      /***********************************************************************
      *                                                                      *
      *  Determine the color of the next adjacent vertex.                    *
      *                                                                      *
      ***********************************************************************/

      if (graph_adjlist(graph, adj_vertex, &clr_adjlist) != 0) {

         mac_queue_destroy(&queue);
         return -1;

      }

      clr_vertex = clr_adjlist->vertex;

      /***********************************************************************
      *                                                                      *
      *  Color each white vertex gray and enqueue its adjacency list.        *
      *                                                                      *
      ***********************************************************************/

      if (clr_vertex->color == white) {

         clr_vertex->color = gray;
         clr_vertex->hops = ((BfsVertex *)adjlist->vertex)->hops + 1;

         if (mac_queue_enqueue(&queue, clr_adjlist) != 0) {

            mac_queue_destroy(&queue);
            return -1;

         }

      }

   }

   /**************************************************************************
   *                                                                         *
   *  Dequeue the current adjacency list and color its vertex black.         *
   *                                                                         *
   **************************************************************************/

   if (mac_queue_dequeue(&queue, (void **)&adjlist) == 0) {

      ((BfsVertex *)adjlist->vertex)->color = black;

      }

   else {

      mac_queue_destroy(&queue);
      return -1;

   }

}

mac_queue_destroy(&queue);

/*****************************************************************************
*                                                                            *
*  Pass back the hop count for each vertex in a list.                        *
*                                                                            *
*****************************************************************************/

mac_list_init(hops, NULL);

for (element = mac_list_head(&graph_adjlists(graph)); element != NULL; element =
   mac_list_next(element)) {

   /**************************************************************************
   *                                                                         *
   *  Skip vertices that were not visited (those with hop counts of -1).     *
   *                                                                         *
   **************************************************************************/

   clr_vertex = ((AdjList *)mac_list_data(element))->vertex;

   if (clr_vertex->hops != -1) {

      if (mac_list_ins_next(hops, mac_list_tail(hops), clr_vertex) != 0) {

         mac_list_destroy(hops);
         return -1;

      }

   }

}

return 0;

}
