/**
 * @file  CListTest.cpp
 * @brief Unit Tests for CLIST
 */

#include "gtest/gtest.h"

#include <cstdio>

extern "C"
{
   #include "Include/CList.h"
}


TEST(CList, CListCreate)
{
   // Arrange
   CLIST* list = NULL;

   // Act
   list = CListCreate();

   // Assert
   ASSERT_FALSE(list == NULL);
}


TEST(CList, CListPushFront_InvPrms_1)
{
   // Arrange
   CLIST* list = NULL;
   STATUS_CODE status = SC_SUCCESS;

   // Act
   list = CListCreate();
   int data = 0;
   status = list->PushFront(NULL, &data, sizeof(int));

   // Assert
   ASSERT_TRUE(SC_ERROR(status));
}


TEST(CList, CListPushFront_InvPrms_2)
{
   // Arrange
   CLIST* list = NULL;
   STATUS_CODE status = SC_SUCCESS;

   // Act
   list = CListCreate();
   int data = 0;
   status = list->PushFront(list, NULL, sizeof(int));

   // Assert
   ASSERT_TRUE(SC_ERROR(status));
}


TEST(CList, CListPushFront_InvPrms_3)
{
   // Arrange
   CLIST* list = NULL;
   STATUS_CODE status = SC_SUCCESS;

   // Act
   list = CListCreate();
   int data = 0;
   status = list->PushFront(list, &data, 0);

   // Assert
   ASSERT_TRUE(SC_ERROR(status));
}


TEST(CList, CListPushFront_ValidPrms)
{
   // Arrange
   CLIST* list = NULL;
   STATUS_CODE status = SC_SUCCESS;

   // Act
   list = CListCreate();
   int data = 0;
   status = list->PushFront(list, &data, sizeof(int));

   // Assert
   ASSERT_FALSE(SC_ERROR(status));
}


TEST(CList, CListFront_ValidPrms_1)
{
   // Arrange
   CLIST* list = NULL;
   STATUS_CODE status = SC_SUCCESS;

   // Act
   list = CListCreate();
   int data = 25;
   status = list->PushFront(list, &data, sizeof(int));
   ASSERT_FALSE(SC_ERROR(status));
   CLIST_NODE* head = list->Front(list);

   // Assert
   ASSERT_FALSE(head == NULL);
}


TEST(CList, CListFront_ValidPrms_2)
{
   // Arrange
   CLIST* list = NULL;
   STATUS_CODE status = SC_SUCCESS;

   // Act
   list = CListCreate();
   CLIST_NODE* head = list->Front(list);

   // Assert
   ASSERT_TRUE(head == NULL);
}


TEST(CList, CListFront_InvPrms)
{
   // Arrange
   CLIST* list = NULL;
   STATUS_CODE status = SC_SUCCESS;

   // Act
   list = CListCreate();
   int data = 25;
   status = list->PushFront(list, &data, sizeof(int));
   ASSERT_FALSE(SC_ERROR(status));
   CLIST_NODE* head = list->Front(NULL);

   // Assert
   ASSERT_TRUE(head == NULL);
}


TEST(CList, CListGetRefToData)
{
   // Arrange
   CLIST* list = NULL;
   STATUS_CODE status = SC_SUCCESS;

   // Act
   list = CListCreate();
   int data = 25;
   status = list->PushFront(list, &data, sizeof(int));
   ASSERT_FALSE(SC_ERROR(status));
   CLIST_NODE* head = list->Front(list);
   ASSERT_FALSE(NULL == head);

   // Assert
   void *pData = NULL;
   size_t *dataSize = NULL;
   status = list->GetRefToData(list, head, &pData, &dataSize);
   ASSERT_FALSE(SC_ERROR(status));
   ASSERT_TRUE(*((int*)pData) == 25);
   ASSERT_TRUE(*dataSize = sizeof(int));
}


int main(int argc, char** argv)
{
   ::testing::InitGoogleTest(&argc, argv);

   return RUN_ALL_TESTS();
}