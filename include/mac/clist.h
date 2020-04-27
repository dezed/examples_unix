/*****************************************************************************
*                                                                            *
*  ------------------------------- clist.h --------------------------------  *
*                                                                            *
*****************************************************************************/

#ifndef CLIST_H
#define CLIST_H

#include <stdlib.h>

/*****************************************************************************
*                                                                            *
*  Define a structure for circular list elements.                            *
*                                                                            *
*****************************************************************************/

typedef struct CListElmt_ {

void               *data;
struct CListElmt_  *next;

} CListElmt;

/*****************************************************************************
*                                                                            *
*  Define a structure for circular lists.                                    *
*                                                                            *
*****************************************************************************/

typedef struct CList_ {

int                size;

int                (*match)(const void *key1, const void *key2);
void               (*destroy)(void *data);

CListElmt          *head;

} CList;

/*****************************************************************************
*                                                                            *
*  --------------------------- Public Interface ---------------------------  *
*                                                                            *
*****************************************************************************/

void mac_clist_init(CList *list, void (*destroy)(void *data));

void mac_clist_destroy(CList *list);

int mac_clist_ins_next(CList *list, CListElmt *element, const void *data);

int mac_clist_rem_next(CList *list, CListElmt *element, void **data);

#define mac_clist_size(list) ((list)->size)

#define mac_clist_head(list) ((list)->head)

#define mac_clist_data(element) ((element)->data)

#define mac_clist_next(element) ((element)->next)

#endif
