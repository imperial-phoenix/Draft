/**
 * @file  CList.c
 * @brief Doubly linked list implementation.
 */

#include <stdlib.h>

#include "Include/CList.h"


////////////////////////////////////////////////////
///             Internal structures              ///
////////////////////////////////////////////////////

/**
 * @struct CLIST_NODE
 * @brief  Doubly Linked List Node.
 */
typedef struct CLIST_NODE
{
   struct CLIST_NODE* Prev; /** Pointer to previous node */
   struct CLIST_NODE* Next; /** Pointer to next node */
   void*              Data; /** Data stored in the node */
} CLIST_NODE;


/**
 * @struct CLIST_IMPL
 * @brief  CList protocol implementation.
 */
typedef struct CLIST_IMPL
{
   CLIST VTable; /** API */

   CLIST_NODE* Head; /** Pointer to the first element in the list */
   CLIST_NODE* Tail; /** Pointer to the last element in the list */
   size_t      Size; /** Number of nodes */
} CLIST_IMPL;



////////////////////////////////////////////////////
///              Internal functions              ///
////////////////////////////////////////////////////


////////////////////////////////////////////////////
///           CList API implementation           ///
////////////////////////////////////////////////////

// size_t
// CListSize(
//    IN CLIST* This)
// {
   
// }



CLIST*
CListCreate()
{
   CLIST_IMPL* this = malloc(sizeof(CLIST_IMPL));
   if (NULL == this) { return NULL; }

   this->Head = this->Tail = NULL;
   this->Size = 0;

   return &this->VTable;
}