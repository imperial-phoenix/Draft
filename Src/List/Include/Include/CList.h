/**
 * @file    CList.h
 * @brief   Doubly linked list declaration.
 * @ingroup DATA_STRUCTURES
 */

#ifndef  __CLIST_H__
#define  __CLIST_H__

#include "Include/Misc.h"


typedef struct CLIST CLIST;
typedef struct CLIST_NODE CLIST_NODE;


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
 * @brief Returns the node with the first element in the list.
 *
 * @param[in]  This  Pointer to CList protocol
 *
 * @retval  NULL         If This is invalid or the list is empty
 * @retval  CLIST_NODE*  Otherwise
 */
typedef
CLIST_NODE*
(*CLIST_FRONT)(
   IN CLIST* This);


/**
 * @brief Get link to data
 *
 * @param[in]  This      Pointer to CList protocol
 * @param[in]  Position  Position in the list
 * @param[in]  Data      Pointer to pointer to data
 * @param[in]  DataSize  Pointer to pointer to data size
 */
typedef
STATUS_CODE
(*CLIST_GET_REF_TO_DATA)(
   IN CLIST*      This,
   IN CLIST_NODE* Position,
   IN void***     Data,
   IN size_t**    DataSize);


/**
 * @brief 
 * 
 * @param[in]  This      Pointer to CList protocol
 * @param[in]  Position  
 */
typedef
CLIST_NODE*
(*CLIST_NEXT)(
   IN CLIST*      This,
   IN CLIST_NODE* Position);


/**
 * @struct CLIST
 * @brief  Doubly Linked List protocol.
 */
typedef struct CLIST
{
   CLIST_PUSH_FRONT      PushFront;
   CLIST_FRONT           Front;
   CLIST_GET_REF_TO_DATA GetRefToData;
   CLIST_NEXT            Next;
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