/**
 * @file    CList.c
 * @brief   Doubly linked list implementation.
 * @ingroup DATA_STRUCTURES
 */

#include <stdlib.h>
#include <string.h>

#include "Include/CList.h"


///////////////////////////////////////////////////////////
//                  Internal structures                  //
///////////////////////////////////////////////////////////


/**
 * @struct CLIST_NODE
 * @brief  Doubly Linked List Node.
 */
typedef struct CLIST_NODE
{
   struct CLIST_NODE* Prev; /** Pointer to previous node */
   struct CLIST_NODE* Next; /** Pointer to next node     */
   void*              Data; /** Data stored in the node  */
} CLIST_NODE;


/**
 * @struct CLIST_IMPL
 * @brief  CList protocol implementation.
 */
typedef struct CLIST_IMPL
{
   STRUCT_ID StructureId; /** Structure unique id */
   CLIST     VTable;      /** API                 */

   CLIST_NODE* Head; /** Pointer to the first element in the list */
   CLIST_NODE* Tail; /** Pointer to the last element in the list  */
   size_t      Size; /** Number of nodes                          */
} CLIST_IMPL;


/** Unique identificator for CLIST_IMPL_IMPL */
#define CLIST_IMPL_STRUCT_ID STRUCT_ID_64('C', 'L', 'I', 'S', 'T', '.', '.', '.')


///////////////////////////////////////////////////////////
//                  Internal functions                   //
///////////////////////////////////////////////////////////


/**
 * Creates CLIST_NODE.
 *
 * @param[in]  Data      Data that will be stored in the node
 * @param[in]  DataSize  Data size
 * @param[in]  Prev      Pointer to previous node
 * @param[in]  Next      Pointer to next node
 *
 * @retval CLIST_NODE* If the node is successfully created
 * @retval NULL        Otherwise
 */
static
CLIST_NODE*
InCreateNode(
   IN void*       Data,
   IN size_t      DataSize,
   IN CLIST_NODE* Prev,
   IN CLIST_NODE* Next)
{
   CLIST_NODE* node = malloc(sizeof(CLIST_NODE));
   if (NULL == node) { return NULL; }

   node->Data = malloc(DataSize);
   if (NULL == node->Data)
   {
      free(node);
      return NULL;
   }

   memcpy(node->Data, Data, DataSize);
   node->Prev = Prev;
   node->Next = Next;

   return node;
}


///////////////////////////////////////////////////////////
//               CList API implementation                //
///////////////////////////////////////////////////////////

/**
 * Inserts a copy of the Data at the beginning of the list.
 *
 * @param[in]  This      Pointer to CList protocol
 * @param[in]  Data      Storage data
 * @param[in]  DataSize  Data size
 */
static
STATUS_CODE
CListPushFront(
   IN CLIST* This,
   IN void*  Data,
   IN size_t DataSize)
{
   STATUS_CODE status = SC_SUCCESS;
   CLIST_NODE* node = NULL;

   do
   {
      GET_THIS(This, CLIST_IMPL);
      if ((NULL == Data) || (0 == DataSize))
      {
         SET_SC(SC_INVALID_PARAMETER);
         break;
      }

      node = InCreateNode(Data, DataSize, NULL, this->Head);
      if (NULL == node) { SET_SC(SC_UNSUCCESSFUL); break; }

      if (0 == this->Size)
      {
         this->Head = this->Tail = node;
      }
      else
      {
         this->Head->Prev = node;
         this->Head = node;
      }

      ++this->Size;

   } while (false);

   return status;
}


/**
 * @brief Returns the node with the first element in the list.
 *
 * @param[in]  This  Pointer to CList protocol
 *
 * @retval  NULL         If This is invalid or the list is empty
 * @retval  CLIST_NODE*  Otherwise
 */
static
CLIST_NODE*
CListFront(
   IN CLIST* This)
{
   STATUS_CODE status = SC_SUCCESS;

   do
   {
      GET_THIS(This, CLIST_IMPL);
      return this->Head;
   } while (false);

   return NULL;
}


CLIST*
CListCreate()
{
   CLIST_IMPL* this = malloc(sizeof(CLIST_IMPL));
   if (NULL == this) { return NULL; }

   this->StructureId = CLIST_IMPL_STRUCT_ID;
   this->Head = this->Tail = NULL;
   this->Size = 0;

   this->VTable.PushFront = CListPushFront;
   this->VTable.Front = CListFront;

   return &this->VTable;
}