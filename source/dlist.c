/*****************************************************************************
 *                                                                            *
 *  ------------------------------- dlist.c --------------------------------  *
 *                                                                            *
 *****************************************************************************/

#include <stdlib.h>
#include <string.h>

#include "mac/dlist.h"

/*****************************************************************************
 *                                                                            *
 *  ------------------------------ mac_dlist_init ------------------------------  *
 *                                                                            *
 *****************************************************************************/
#if 0
void mac_dlist_init(DList *list, void (*destroy)(void *data)) {

	/*****************************************************************************
	 *                                                                            *
	 *  Initialize the list.                                                      *
	 *                                                                            *
	 *****************************************************************************/

	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
	list->tail = NULL;
	list->el_size = sizeof( void* );

	return;

}
#else
void mac_dlist_init(DList *list, size_t el_size, void (*destroy)(void *data)) {

	/*****************************************************************************
	 *                                                                            *
	 *  Initialize the list.                                                      *
	 *                                                                            *
	 *****************************************************************************/

	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
	list->tail = NULL;

	list->el_size = el_size;
	return;

}
#endif

/*****************************************************************************
 *                                                                            *
 *  ---------------------------- mac_dlist_destroy -----------------------------  *
 *                                                                            *
 *****************************************************************************/

void mac_dlist_destroy(DList *list) {

	void               *data;

	/*****************************************************************************
	 *                                                                            *
	 *  Remove each element.                                                      *
	 *                                                                            *
	 *****************************************************************************/

	while (mac_dlist_size(list) > 0) {

		if (mac_dlist_remove(list, mac_dlist_tail(list), (void **)&data) == 0 && list->
				destroy != NULL) {

			/***********************************************************************
			 *                                                                      *
			 *  Call a user-defined function to free dynamically allocated data.    *
			 *                                                                      *
			 ***********************************************************************/

			list->destroy(data);

		}

	}

	/*****************************************************************************
	 *                                                                            *
	 *  No operations are allowed now, but clear the structure as a precaution.   *
	 *                                                                            *
	 *****************************************************************************/

	memset(list, 0, sizeof(DList));

	return;

}

/*****************************************************************************
 *                                                                            *
 *  ---------------------------- mac_dlist_ins_next ----------------------------  *
 *                                                                            *
 *****************************************************************************/
#if 0
int mac_dlist_ins_next(DList *list, DListElmt *element, const void *data) {

	DListElmt          *new_element;

	/*****************************************************************************
	 *                                                                            *
	 *  Do not allow a NULL element unless the list is empty.                     *
	 *                                                                            *
	 *****************************************************************************/

	if (element == NULL && mac_dlist_size(list) != 0)
		return -1;

	/*****************************************************************************
	 *                                                                            *
	 *  Allocate storage for the element.                                         *
	 *                                                                            *
	 *****************************************************************************/

	if ((new_element = (DListElmt *)malloc(sizeof(DListElmt))) == NULL)
		return -1;

	/*****************************************************************************
	 *                                                                            *
	 *  Insert the new element into the list.                                     *
	 *                                                                            *
	 *****************************************************************************/
#if 0
	new_element->data = (void *)data;
#else
	new_element->data = malloc( list->el_size );
	memcpy( new_element->data, data, list->el_size );
#endif


	if (mac_dlist_size(list) == 0) {

		/**************************************************************************
		 *                                                                         *
		 *  Handle insertion when the list is empty.                               *
		 *                                                                         *
		 **************************************************************************/

		list->head = new_element;
		list->head->prev = NULL;
		list->head->next = NULL;
		list->tail = new_element;

	}

	else {

		/**************************************************************************
		 *                                                                         *
		 *  Handle insertion when the list is not empty.                           *
		 *                                                                         *
		 **************************************************************************/

		new_element->next = element->next;
		new_element->prev = element;

		if (element->next == NULL)
			list->tail = new_element;
		else
			element->next->prev = new_element;

		element->next = new_element;

	}

	/*****************************************************************************
	 *                                                                            *
	 *  Adjust the size of the list to account for the inserted element.          *
	 *                                                                            *
	 *****************************************************************************/

	list->size++;

	return 0;

}
#else


int mac_dlist_ins_next(DList *list, DListElmt *element, const void *data) {

	DListElmt          *new_element;

	/*****************************************************************************
	 *                                                                            *
	 *  Do not allow a NULL element unless the list is empty.                     *
	 *                                                                            *
	 *****************************************************************************/

	if (element == NULL && mac_dlist_size(list) != 0)
		return -1;

	/*****************************************************************************
	 *                                                                            *
	 *  Allocate storage for the element.                                         *
	 *                                                                            *
	 *****************************************************************************/

	if ((new_element = (DListElmt *)malloc(sizeof(DListElmt))) == NULL)
		return -1;

	/*****************************************************************************
	 *                                                                            *
	 *  Insert the new element into the list.                                     *
	 *                                                                            *
	 *****************************************************************************/
#if 0
	new_element->data = (void *)data;
#else
	new_element->data = malloc( list->el_size );
	memcpy( new_element->data, data, list->el_size );
#endif
	if (mac_dlist_size(list) == 0) {

		/**************************************************************************
		 *                                                                         *
		 *  Handle insertion when the list is empty.                               *
		 *                                                                         *
		 **************************************************************************/

		list->head = new_element;
		list->head->prev = NULL;
		list->head->next = NULL;
		list->tail = new_element;

	}

	else {

		/**************************************************************************
		 *                                                                         *
		 *  Handle insertion when the list is not empty.                           *
		 *                                                                         *
		 **************************************************************************/

		new_element->next = element->next;
		new_element->prev = element;

		if (element->next == NULL)
			list->tail = new_element;
		else
			element->next->prev = new_element;

		element->next = new_element;

	}

	/*****************************************************************************
	 *                                                                            *
	 *  Adjust the size of the list to account for the inserted element.          *
	 *                                                                            *
	 *****************************************************************************/

	list->size++;

	return 0;

}
#endif

/*****************************************************************************
 *                                                                            *
 *  ---------------------------- mac_dlist_ins_prev ----------------------------  *
 *                                                                            *
 *****************************************************************************/


int mac_dlist_ins_prev(DList *list, DListElmt *element, const void *data) {

	DListElmt          *new_element;

	/*****************************************************************************
	 *                                                                            *
	 *  Do not allow a NULL element unless the list is empty.                     *
	 *                                                                            *
	 *****************************************************************************/

	if (element == NULL && mac_dlist_size(list) != 0)
		return -1;

	/*****************************************************************************
	 *                                                                            *
	 *  Allocate storage to be managed by the abstract data type.                 *
	 *                                                                            *
	 *****************************************************************************/

	if ((new_element = (DListElmt *)malloc(sizeof(DListElmt))) == NULL)
		return -1;

	/*****************************************************************************
	 *                                                                            *
	 *  Insert the new element into the list.                                     *
	 *                                                                            *
	 *****************************************************************************/
#if 0
	new_element->data = (void *)data;
#else
	new_element->data = malloc( list->el_size );
	memcpy( new_element->data, data, list->el_size );
#endif

	if (mac_dlist_size(list) == 0) {

		/**************************************************************************
		 *                                                                         *
		 *  Handle insertion when the list is empty.                               *
		 *                                                                         *
		 **************************************************************************/

		list->head = new_element;
		list->head->prev = NULL;
		list->head->next = NULL;
		list->tail = new_element;

	}


	else {

		/**************************************************************************
		 *                                                                         *
		 *  Handle insertion when the list is not empty.                           *
		 *                                                                         *
		 **************************************************************************/

		new_element->next = element; 
		new_element->prev = element->prev;

		if (element->prev == NULL)
			list->head = new_element;
		else
			element->prev->next = new_element;

		element->prev = new_element;

	}


	/*****************************************************************************
	 *                                                                            *
	 *  Adjust the size of the list to account for the new element.               *
	 *                                                                            *
	 *****************************************************************************/

	list->size++;

	return 0;

}

int mac_dlist_ins_prev2(DList *list, DListElmt *element, const void *data) {

	DListElmt          *new_element;

	/*****************************************************************************
	 *                                                                            *
	 *  Do not allow a NULL element unless the list is empty.                     *
	 *                                                                            *
	 *****************************************************************************/

	if (element == NULL && mac_dlist_size(list) != 0)
		return -1;

	/*****************************************************************************
	 *                                                                            *
	 *  Allocate storage to be managed by the abstract data type.                 *
	 *                                                                            *
	 *****************************************************************************/

	if ((new_element = (DListElmt *)malloc(sizeof(DListElmt))) == NULL)
		return -1;

	/*****************************************************************************
	 *                                                                            *
	 *  Insert the new element into the list.                                     *
	 *                                                                            *
	 *****************************************************************************/
#if 0
	new_element->data = (void *)data;
#else
	new_element->data = malloc( list->el_size );
	memcpy( new_element->data, data, list->el_size );
#endif

	if (mac_dlist_size(list) == 0) {

		/**************************************************************************
		 *                                                                         *
		 *  Handle insertion when the list is empty.                               *
		 *                                                                         *
		 **************************************************************************/

		list->head = new_element;
		list->head->prev = NULL;
		list->head->next = NULL;
		list->tail = new_element;

	}


	else {

		/**************************************************************************
		 *                                                                         *
		 *  Handle insertion when the list is not empty.                           *
		 *                                                                         *
		 **************************************************************************/

		new_element->next = element; 
		new_element->prev = element->prev;

		if (element->prev == NULL)
			list->head = new_element;
		else
			element->prev->next = new_element;

		element->prev = new_element;

	}


	/*****************************************************************************
	 *                                                                            *
	 *  Adjust the size of the list to account for the new element.               *
	 *                                                                            *
	 *****************************************************************************/

	list->size++;

	return 0;

}


/*****************************************************************************
 *                                                                            *
 *  ----------------------------- mac_dlist_remove -----------------------------  *
 *                                                                            *
 *****************************************************************************/

int mac_dlist_remove(DList *list, DListElmt *element, void **data) {

	/*****************************************************************************
	 *                                                                            *
	 *  Do not allow a NULL element or removal from an empty list.                *
	 *                                                                            *
	 *****************************************************************************/

	if (element == NULL || mac_dlist_size(list) == 0)
		return -1;

	/*****************************************************************************
	 *                                                                            *
	 *  Remove the element from the list.                                         *
	 *                                                                            *
	 *****************************************************************************/

	*data = element->data;

	if (element == list->head) {

		/**************************************************************************
		 *                                                                         *
		 *  Handle removal from the head of the list.                              *
		 *                                                                         *
		 **************************************************************************/

		list->head = element->next;

		if (list->head == NULL)
			list->tail = NULL;
		else
			element->next->prev = NULL;

	}

	else {

		/**************************************************************************
		 *                                                                         *
		 *  Handle removal from other than the head of the list.                   *
		 *                                                                         *
		 **************************************************************************/

		element->prev->next = element->next;

		if (element->next == NULL)
			list->tail = element->prev;
		else
			element->next->prev = element->prev;

	}

	/*****************************************************************************
	 *                                                                            *
	 *  Free the storage allocated by the abstract data type.                     *
	 *                                                                            *
	 *****************************************************************************/

	free(element);

	/*****************************************************************************
	 *                                                                            *
	 *  Adjust the size of the list to account for the removed element.           *
	 *                                                                            *
	 *****************************************************************************/

	list->size--;

	return 0;

}
