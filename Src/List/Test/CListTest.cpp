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


int main(int argc, char** argv)
{
   ::testing::InitGoogleTest(&argc, argv);

   return RUN_ALL_TESTS();
}