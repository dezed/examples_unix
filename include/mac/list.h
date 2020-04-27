/*****************************************************************************
*                                                                            *
*  -------------------------------- list.h --------------------------------  *
*                                                                            *
*****************************************************************************/

#ifndef MAC_LIST_H
#define MAC_LIST_H

#include <stdlib.h>

/*****************************************************************************
*                                                                            *
*  Define a structure for linked list elements.                              *
*                                                                            *
*****************************************************************************/

typedef struct ListElmt_ {

void               *data;
struct ListElmt_   *next;

} ListElmt;

typedef ListElmt mac_list_node_t;

/*****************************************************************************
*                                                                            *
*  Define a structure for linked lists.                                      *
*                                                                            *
*****************************************************************************/

typedef struct List_ {

int                size;
size_t el_size;

int                (*match)(const void *key1, const void *key2);
void               (*destroy)(void *data);

ListElmt           *head;
ListElmt           *tail;

} List;

typedef List mac_list_t;

/*****************************************************************************
*                                                                            *
*  --------------------------- Public Interface ---------------------------  *
*                                                                            *
*****************************************************************************/
#if 0
void mac_list_init(List *list, void (*destroy)(void *data));
#else
void mac_list_init(List *list, size_t el_size, void (*destroy)(void *data));
#endif

void mac_list_destroy(List *list);

#if 0
int mac_list_ins_next(List *list, ListElmt *element, const void *data);
#else
int mac_list_ins_next(List *list, ListElmt *element, const void *data);
#endif

int mac_list_rem_next(List *list, ListElmt *element, void **data);

#define mac_list_size(list) ((list)->size)

#define mac_list_head(list) ((list)->head)

#define mac_list_tail(list) ((list)->tail)

#define mac_list_is_head(list, element) ((element) == (list)->head ? 1 : 0)

#define mac_list_is_tail(element) ((element)->next == NULL ? 1 : 0)

#define mac_list_data(element) ((element)->data)

#define mac_list_next(element) ((element)->next)

#endif
