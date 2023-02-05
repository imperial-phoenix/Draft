/**
 * @file  CList.h
 * @brief Doubly linked list declaration.
 */

#ifndef  __CLIST_H__
#define  __CLIST_H__

#include "Include/Common.h"


typedef struct CLIST CLIST;


// typedef
// size_t
// (*CLIST_SIZE)(
//    IN CLIST* This);


/**
 * @struct CLIST
 * @brief  Doubly Linked List protocol.
 */
typedef struct CLIST
{
   // CLIST_SIZE Size;
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