/**
 * @file    CList.h
 * @brief   Doubly linked list declaration.
 * @ingroup DATA_STRUCTURES
 */

#ifndef  __CLIST_H__
#define  __CLIST_H__

#include "Include/Misc.h"


typedef struct CLIST CLIST;


/**
 * Inserts a copy of the Data at the beginning of the list.
 *
 * @param[in]  This      Pointer to CList protocol
 * @param[in]  Data      Storage data
 * @param[in]  DataSize  Data size
 */
typedef
STATUS_CODE
(*CLIST_PUSH_FRONT)(
   IN CLIST* This,
   IN void*  Data,
   IN size_t DataSize);


/**
 * @struct CLIST
 * @brief  Doubly Linked List protocol.
 */
typedef struct CLIST
{
   CLIST_PUSH_FRONT PushFront;
} CLIST;


/**
 * @brief Creates a doubly linked list protocol.
 * 
 * @return On succress, returns the pointer to doubly linked list protocol.
 *         On failure, returns a NULL pointer.
 */
CLIST*
CListCreate();

#endif  // __CLIST_H__