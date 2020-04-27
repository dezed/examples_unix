/*****************************************************************************
 *                                                                            *
 *  ------------------------------- dlist.h --------------------------------  *
 *                                                                            *
 *****************************************************************************/

#ifndef MAC_DLIST_H
#define MAC_DLIST_H

#include <stdlib.h>

/*****************************************************************************
 *                                                                            *
 *  Define a structure for doubly-linked list elements.                       *
 *                                                                            *
 *****************************************************************************/

typedef struct DListElmt_ {

	void               *data;
	struct DListElmt_  *prev;
	struct DListElmt_  *next;

} DListElmt;

typedef DListElmt mac_dlist_node_t;


/*****************************************************************************
 *                                                                            *
 *  Define a structure for doubly-linked lists.                               *
 *                                                                            *
 *****************************************************************************/

typedef struct DList_ {

	int                size;

	size_t el_size;
	int                (*match)(const void *key1, const void *key2);
	void               (*destroy)(void *data);

	DListElmt          *head;
	DListElmt          *tail;

} DList;

typedef DList mac_dlist_t;
/*****************************************************************************
 *                                                                            *
 *  --------------------------- Public Interface ---------------------------  *
 *                                                                            *
 *****************************************************************************/
#if 0
void mac_dlist_init(DList *list, void (*destroy)(void *data));
#else
void mac_dlist_init(DList *list, size_t el_size, void (*destroy)(void *data));
#endif

void mac_dlist_destroy(DList *list);


int mac_dlist_ins_next(DList *list, DListElmt *element, const void *data);

int mac_dlist_ins_prev(DList *list, DListElmt *element, const void *data);

int mac_dlist_remove(DList *list, DListElmt *element
#if 0
		, void **data
#endif
		);


#define mac_dlist_size(list) ((list)->size)

#define mac_dlist_head(list) ((list)->head)

#define mac_dlist_tail(list) ((list)->tail)

#define mac_dlist_is_head(element) ((element)->prev == NULL ? 1 : 0)

#define mac_dlist_is_tail(element) ((element)->next == NULL ? 1 : 0)

#define mac_dlist_data(element) ((element)->data)

#define mac_dlist_next(element) ((element)->next)

#define mac_dlist_prev(element) ((element)->prev)

#endif
