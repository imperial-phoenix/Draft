// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

/**
 * @file     CList.c
 * @brief    Doubly linked list implementation.
 * @ingroup  DATA_STRUCTURES
 */

#include <stdlib.h>
#include <string.h>

#include "Include/CList.h"


///////////////////////////////////////////////////////////
///                 Internal structures                 ///
///////////////////////////////////////////////////////////


/** Doubly linked list node. */
typedef struct CLIST_NODE
{
   struct CLIST_NODE* Prev;     /** Pointer to previous node */
   struct CLIST_NODE* Next;     /** Pointer to next node     */
   void*              Data;     /** Data stored in the node  */
   size_t             DataSize; /** Size of data stored in the node */
} CLIST_NODE;


/** CList protocol implementation. */
typedef struct CLIST_IMPL
{
   STRUCT_ID StructureId; /** Structure unique id */
   CLIST     VTable;      /** API                 */

   CLIST_NODE* Head; /** Pointer to the first node in the list */
   CLIST_NODE* Tail; /** Pointer to the last node in the list  */
   size_t      Size; /** Number of nodes */
} CLIST_IMPL;


/** Unique identificator for CLIST_IMPL_IMPL */
#define CLIST_IMPL_STRUCT_ID STRUCT_ID_64('C', 'L', 'I', 'S', 'T', '.', '.', '.')


///////////////////////////////////////////////////////////
///                 Internal functions                  ///
///////////////////////////////////////////////////////////


/**
 * Creates CLIST_NODE.
 *
 * @param[in]  Data      Data that will be stored in the node
 * @param[in]  DataSize  Data size
 * @param[in]  Prev      Pointer to previous node
 * @param[in]  Next      Pointer to next node
 *
 * @retval  CLIST_NODE*  If the node is successfully created
 * @retval  NULL         On failure
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
   node->DataSize = DataSize;

   return node;
}


///////////////////////////////////////////////////////////
///              CList API implementation               ///
///////////////////////////////////////////////////////////

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
 * Returns the first node in the list.
 *
 * @param[in]  This  Pointer to CList protocol
 *
 * @retval  NULL         If This is invalid or the list is empty
 * @retval  CLIST_NODE*  List head
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
static
STATUS_CODE
CListGetRefToData(
   IN CLIST*      This,
   IN CLIST_NODE* Position,
   IN void***     Data,
   IN size_t**    DataSize)
{
   STATUS_CODE status = SC_SUCCESS;

   do
   {
      GET_THIS(This, CLIST_IMPL);
      if ((NULL == Position) || (NULL == Data) || (NULL == DataSize))
      {
         SET_SC(SC_INVALID_PARAMETER);
         break;
      }

      *Data = &Position->Data;
      *DataSize = &Position->DataSize;

   } while (false);

   return status;
}


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
static
STATUS_CODE
CListGetCopyData(
   IN CLIST*      This,
   IN CLIST_NODE* Position,
   OUT void**     Data,
   OUT size_t*    DataSize)
{
   STATUS_CODE status = SC_SUCCESS;

   do
   {
      GET_THIS(This, CLIST_IMPL);

      if ((NULL == Position) || (NULL == Data) || (NULL == DataSize))
      {
         SET_SC(SC_INVALID_PARAMETER);
         break;
      }

      *Data = malloc(Position->DataSize);
      if (NULL == *Data) { SET_SC(SC_NOT_ENOUGH_MEMORY); break; }

      memcpy(*Data, Position->Data, Position->DataSize);
      *DataSize = Position->DataSize;

   } while (false);

   return status;
}


/**
 * Returns the previous node in the list.
 *
 * @param[in]  This      Pointer to CList protocol
 * @param[in]  Position  Position in the list
 *
 * @retval  CLIST_NODE*  Next node
 * @retval  NULL         If Invalid input parameter or there is no previous node
 */
static
CLIST_NODE*
CListPrev(
   IN CLIST*      This,
   IN CLIST_NODE* Position)
{
   STATUS_CODE status = SC_SUCCESS;

   do
   {
      GET_THIS(This, CLIST_IMPL);
      if (NULL == Position) { SET_SC(SC_INVALID_PARAMETER); break; }

      return Position->Prev;

   } while (false);

   return NULL;
}


/**
 * Returns the next node in the list.
 *
 * @param[in]  This      Pointer to CList protocol
 * @param[in]  Position  Position in the list
 *
 * @retval  CLIST_NODE*  Next node
 * @retval  NULL         If Invalid input parameter or there is no next node
 */
static
CLIST_NODE*
CListNext(
   IN CLIST*      This,
   IN CLIST_NODE* Position)
{
   STATUS_CODE status = SC_SUCCESS;

   do
   {
      GET_THIS(This, CLIST_IMPL);
      if (NULL == Position) { SET_SC(SC_INVALID_PARAMETER); break; }

      return Position->Next;

   } while (false);

   return NULL;
}


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
static
STATUS_CODE
CListInsertBefore(
   IN CLIST* This,
   IN CLIST_NODE* Position,
   IN void* Data,
   IN size_t DataSize)
{
   STATUS_CODE status = SC_SUCCESS;

   do
   {
      GET_THIS(This, CLIST_IMPL);
      if ((NULL == Position) || (NULL == Data) || (0 == DataSize))
      {
         SET_SC(SC_INVALID_PARAMETER);
         break;
      }

      CLIST_NODE* node = InCreateNode(Data, DataSize, Position->Prev, Position);
      if (NULL == node) { SET_SC(SC_UNSUCCESSFUL); break; }

      if(Position->Prev != NULL)
      {
         Position->Prev->Next = node;
      }
      else
      {
         this->Head = node;
         Position->Prev = node;
      }

      ++this->Size;

   } while (false);

   return status;
}


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
static
STATUS_CODE
CListInsertAfter(
   IN CLIST* This,
   IN CLIST_NODE* Position,
   IN void* Data,
   IN size_t DataSize)
{
   STATUS_CODE status = SC_SUCCESS;

   do
   {
      GET_THIS(This, CLIST_IMPL);
      if ((NULL == Position) || (NULL == Data) || (0 == DataSize))
      {
         SET_SC(SC_INVALID_PARAMETER);
         break;
      }

      CLIST_NODE* node = InCreateNode(Data, DataSize, Position, Position->Next);
      if (NULL == node) { SET_SC(SC_UNSUCCESSFUL); break; }
      Position->Next = node;
      if (node->Next != NULL)
      {
         node->Next->Prev = node;
      }
      else
      {
         this->Tail = node;
      }

      ++this->Size;

   } while (false);

   return status;
}


/**
 * Removes the first node in the list.
 *
 * @param[in]  This  Pointer to CList protocol
 *
 * @retval  SC_INVALID_PARAMETER  Invalid input parameter
 * @retval  SC_SUCCESS            On success
 */
void
CListPopFront(
   IN CLIST* This)
{
   STATUS_CODE status = SC_SUCCESS;

   do
   {
      GET_THIS(This, CLIST_IMPL);

      if (0 == this->Size)
      {
         return;
      }
      else if (1 == this->Size)
      {
         free(this->Head->Data);
         free(this->Head);
         this->Head = this->Tail = NULL;

         --this->Size;
      }
      else
      {
         CLIST_NODE* tmp = this->Head;
         this->Head = tmp->Next;
         this->Head->Prev = tmp->Prev;
         free(tmp->Data);
         free(tmp);
         --this->Size;
      }

   } while (false);

}


/**
 * Returns the number of nodes.
 *
 * @param[in]  This  Pointer to CList protocol
 *
 * @return  Number of nodes. If This is invalid then returns 0.
 */
size_t
CListSize(
   IN CLIST* This)
{
   STATUS_CODE status = SC_SUCCESS;

   do
   {
      GET_THIS(This, CLIST_IMPL);
      return this->Size;
   } while (false);

   return 0;
}


/**
 * Returns the node with the last elemet in the list.
 *
 * @param[in]  This  Pointer to CList protocol
 *
 * @retval  NULL         If This is invalid or the list is empty
 * @retval  CLIST_NODE*  List tail
 */
CLIST_NODE*
CListBack(
   IN CLIST* This)
{
   STATUS_CODE status = SC_SUCCESS;

   do
   {
      GET_THIS(This, CLIST_IMPL);
      return this->Tail;
   } while (false);

   return NULL;
}


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
static
STATUS_CODE
CListPushBack(
   IN CLIST* This,
   IN void*  Data,
   IN size_t DataSize)
{
   STATUS_CODE status = SC_SUCCESS;

   do
   {
      GET_THIS(This, CLIST_IMPL);
      if (NULL == Data || 0 == DataSize)
      {
         SET_SC(SC_INVALID_PARAMETER);
         break;
      }

      CLIST_NODE* node = InCreateNode(Data, DataSize, this->Tail, NULL);

      if (0 == this->Size)
      {
         this->Head = this->Tail = node;
      }
      else
      {
         this->Tail->Next = node;
         this->Tail = node;
      }

      ++this->Size;

   } while (false);

   return status;
}


CLIST*
CListCreate()
{
   CLIST_IMPL* this = malloc(sizeof(CLIST_IMPL));
   if (NULL == this) { return NULL; }

   this->StructureId = CLIST_IMPL_STRUCT_ID;
   this->Head = this->Tail = NULL;
   this->Size = 0;

   this->VTable.PushFront    = CListPushFront;
   this->VTable.Front        = CListFront;
   this->VTable.GetRefToData = CListGetRefToData;
   this->VTable.Next         = CListNext;
   this->VTable.GetCopyData  = CListGetCopyData;
   this->VTable.InsertAfter  = CListInsertAfter;
   this->VTable.InsertBefore = CListInsertBefore;
   this->VTable.Prev         = CListPrev;
   this->VTable.PopFront     = CListPopFront;
   this->VTable.Size         = CListSize;
   this->VTable.Back         = CListBack;
   this->VTable.PushBack     = CListPushBack;
   this->VTable.PopBack      = NULL;

   return &this->VTable;
}