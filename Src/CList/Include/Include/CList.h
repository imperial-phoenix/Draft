/**
 * @file     CList.h
 * @brief    Doubly linked list protocol declaration.
 * @ingroup  DATA_STRUCTURES
 */

#ifndef  __CLIST_H__
#define  __CLIST_H__

#include "Include/Misc.h"


/** Doubly linked list protocol. */
typedef struct CLIST CLIST;

/** Doubly linked list node.*/
typedef struct CLIST_NODE CLIST_NODE;


/**
 * Creates a node with a copy of the Data at the head of the list.
 *
 * @param[in]  This      Pointer to CList protocol
 * @param[in]  Data      Data
 * @param[in]  DataSize  Data size
 *
 * @retval  SC_INVALID_PARAMETER  Invalid input parameter
 * @retval  SC_SUCCESS            On success
 * @retval  SC_UNSUCCESSFUL       On failure
 */
typedef
STATUS_CODE
(*CLIST_PUSH_FRONT)(
   IN CLIST* This,
   IN void*  Data,
   IN size_t DataSize);


/**
 * Creates a node with a copy of the Data at the end of the list.
 *
 * @param[in]  This      Pointer to CList protocol
 * @param[in]  Data      Data
 * @param[in]  DataSize  Data size
 *
 * @retval  SC_INVALID_PARAMETER  Invalid input parameter
 * @retval  SC_SUCCESS            On success
 * @retval  SC_UNSUCCESSFUL       On failure
 */
typedef
STATUS_CODE
(*CLIST_PUSH_BACK)(
   IN CLIST* This,
   IN void*  Data,
   IN size_t DataSize);


/**
 * Returns the first node in the list.
 *
 * @param[in]  This  Pointer to CList protocol
 *
 * @retval  NULL         If This is invalid or the list is empty
 * @retval  CLIST_NODE*  List head
 */
typedef
CLIST_NODE*
(*CLIST_FRONT)(
   IN CLIST* This);


/**
 * Returns the node with the last elemet in the list.
 *
 * @param[in]  This  Pointer to CList protocol
 *
 * @retval  NULL         If This is invalid or the list is empty
 * @retval  CLIST_NODE*  List tail
 */
typedef
CLIST_NODE*
(*CLIST_BACK)(
   IN CLIST* This);


/**
 * Removes the first node in the list.
 *
 * @param[in]  This  Pointer to CList protocol
 *
 * @retval  SC_INVALID_PARAMETER  Invalid input parameter
 * @retval  SC_SUCCESS            On success
 */
typedef
void
(*CLIST_POP_FRONT)(
   IN CLIST* This);


/**
 * Removes the last node in the list.
 *
 * @param[in]  This  Pointer to CList protocol
 *
 * @retval  SC_INVALID_PARAMETER  Invalid input parameter
 * @retval  SC_SUCCESS            On success
 */
typedef
void
(*CLIST_POP_BACK)(
   IN CLIST* This);


/**
 * Gets a link to the data stored in the Position node.
 *
 * @param[in]  This      Pointer to CList protocol
 * @param[in]  Position  Position in the list
 * @param[in]  Data      Triple pointer to data
 * @param[in]  DataSize  Pointer to pointer to data size
 *
 * @retval  SC_INVALID_PARAMETER  Invalid input parameter
 * @retval  SC_SUCCESS            On success
 */
typedef
STATUS_CODE
(*CLIST_GET_REF_TO_DATA)(
   IN CLIST*      This,
   IN CLIST_NODE* Position,
   IN void***     Data,
   IN size_t**    DataSize);


/**
 * Gets a copy of the data stored in the Position node.
 *
 * @param[in]   This      Pointer to CList protocol
 * @param[in]   Position  Position in the list
 * @param[out]  Data      Data
 * @param[out]  DataSize  Data size
 *
 * @retval  SC_INVALID_PARAMETER  Invalid input parameter
 * @retval  SC_NOT_ENOUGH_MEMORY  Memory allocation error
 * @retval  SC_SUCCESS            On success
 */
typedef
STATUS_CODE
(*CLIST_GET_COPY_DATA)(
   IN CLIST*      This,
   IN CLIST_NODE* Position,
   OUT void**     Data,
   OUT size_t*    DataSize);


/**
 * Returns the previous node in the list.
 *
 * @param[in]  This      Pointer to CList protocol
 * @param[in]  Position  Position in the list
 *
 * @retval  CLIST_NODE*  Next node
 * @retval  NULL         If Invalid input parameter or there is no previous node
 */
typedef
CLIST_NODE*
(*CLIST_PREV)(
   IN CLIST*      This,
   IN CLIST_NODE* Position);


/**
 * Returns the next node in the list.
 *
 * @param[in]  This      Pointer to CList protocol
 * @param[in]  Position  Position in the list
 *
 * @retval  CLIST_NODE*  Next node
 * @retval  NULL         If Invalid input parameter or there is no next node
 */
typedef
CLIST_NODE*
(*CLIST_NEXT)(
   IN CLIST*      This,
   IN CLIST_NODE* Position);


/**
 * Creates a node with a copy of the Data after Position node.
 *
 * @param[in]  This      Pointer to CList protocol
 * @param[in]  Position  Position in the list
 * @param[in]  Data      Data
 * @param[in]  DataSize  Data size
 *
 * @retval  SC_INVALID_PARAMETER  Invalid input parameter
 * @retval  SC_SUCCESS            On success
 * @retval  SC_UNSUCCESSFUL       Otherwise
 */
typedef
STATUS_CODE
(*CLIST_INSERT_AFTER)(
   IN CLIST*      This,
   IN CLIST_NODE* Position,
   IN void*       Data,
   IN size_t      DataSize);


/**
 * Creates a node with a copy of the Data before Position node.
 *
 * @param[in]  This      Pointer to CList protocol
 * @param[in]  Position  Position in the list
 * @param[in]  Data      Data
 * @param[in]  DataSize  Data size
 *
 * @retval  SC_INVALID_PARAMETER  Invalid input parameter
 * @retval  SC_SUCCESS            On success
 * @retval  SC_UNSUCCESSFUL       Otherwise
 */
typedef
STATUS_CODE
(*CLIST_INSERT_BEFORE)(
   IN CLIST*      This,
   IN CLIST_NODE* Position,
   IN void*       Data,
   IN size_t      DataSize);


/**
 * Returns the number of nodes.
 *
 * @param[in]  This  Pointer to CList protocol
 *
 * @return  Number of nodes. If This is invalid then returns 0.
 */
typedef
size_t
(*CLIST_SIZE)(
   IN CLIST* This);


/// @todo Clear
/// @todo Remove
/// @todo CListDelete
/** Doubly Linked List protocol. */
typedef struct CLIST
{
   CLIST_PUSH_FRONT      PushFront;    /** Creates a node at the beginning */
   CLIST_PUSH_BACK       PushBack;     /** Creates a node at the end */
   CLIST_FRONT           Front;        /** Returns the first node */
   CLIST_BACK            Back;         /** Returns the last node */
   CLIST_POP_FRONT       PopFront;     /** Remove the first node */
   CLIST_POP_BACK        PopBack;      /** Remove the last node */
   CLIST_NEXT            Next;         /** Returns the the next node */
   CLIST_PREV            Prev;         /** Returns the previous node */
   CLIST_GET_REF_TO_DATA GetRefToData; /** Get link to data */
   CLIST_GET_COPY_DATA   GetCopyData;  /** Get a copy of the data */
   CLIST_INSERT_BEFORE   InsertBefore; /** Creates a node before the specified node */
   CLIST_INSERT_AFTER    InsertAfter;  /** Creates a node after the specified node */
   CLIST_SIZE            Size;         /** Returns the number of nodes */
} CLIST;


/**
 * Creates a doubly linked list protocol.
 *
 * @return  On success, returns the pointer to doubly linked list protocol.
 *          On failure, returns a NULL pointer.
 */
CLIST*
CListCreate();

#endif  // __CLIST_H__