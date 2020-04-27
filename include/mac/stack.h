/*****************************************************************************
*                                                                            *
*  ------------------------------- stack.h --------------------------------  *
*                                                                            *
*****************************************************************************/

#ifndef MAC_STACK_H
#define MAC_STACK_H

#include <stdlib.h>

#include "list.h"

/*****************************************************************************
*                                                                            *
*  Implement stacks as linked lists.                                         *
*                                                                            *
*****************************************************************************/

typedef List Stack;

typedef Stack mac_stack_t;

/*****************************************************************************
*                                                                            *
*  --------------------------- Public Interface ---------------------------  *
*                                                                            *
*****************************************************************************/

#define mac_stack_init mac_list_init

#define mac_stack_destroy mac_list_destroy

int mac_stack_push(Stack *stack, const void *data);

int mac_stack_pop(Stack *stack, void **data);

#define mac_stack_peek(stack) ((stack)->head == NULL ? NULL : (stack)->head->data)

#define mac_stack_size mac_list_size

#endif
