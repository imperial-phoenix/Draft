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


///////////////////////////////////////////////////////////
//                    CList Fixtures                     //
///////////////////////////////////////////////////////////

struct CListEmpty : public testing::Test
{
   CLIST* list = NULL;

   // Per-test set-up
   void SetUp() override
   {
      list = CListCreate();
      ASSERT_FALSE(list == NULL);
   }

   // You can define per-test tear-down logic as usual
   void TearDown() override
   {
      // Nothing to do for now
   }

};


struct CListTwentyFiveElement : public testing::Test
{
   CLIST* list = NULL;

   // Per-test set-up
   void SetUp() override
   {
      list = CListCreate();
      ASSERT_FALSE(list == NULL);

      STATUS_CODE status = SC_SUCCESS;
      for (size_t i = 0; i < 25; ++i)
      {
         status = list->PushFront(list, &i, sizeof(size_t));
         ASSERT_FALSE(SC_ERROR(status));
      }
   }

   // You can define per-test tear-down logic as usual
   void TearDown() override
   {
      // Nothing to do for now
   }

};


///////////////////////////////////////////////////////////
//                      CListCreate                      //
///////////////////////////////////////////////////////////

TEST(CListCreate, CorrectCreation)
{
   /*** Arrange ***/
   CLIST *list = NULL;
   STATUS_CODE status = SC_SUCCESS;

   /*** Act ***/
   list = CListCreate();

   /*** Assert ***/
   EXPECT_FALSE(NULL == list);
}

///////////////////////////////////////////////////////////
//                       PushFront                       //
///////////////////////////////////////////////////////////

TEST_F(CListEmpty, PushFrontInvPrms)
{
   /*** Arrange ***/
   STATUS_CODE status = SC_SUCCESS;

   /*** Act && Assert ***/
   status = list->PushFront(NULL, NULL, 0);
   EXPECT_TRUE(SC_ERROR(status));

   status = list->PushFront(list, NULL, 0);
   EXPECT_TRUE(SC_ERROR(status));

   int data = 25;
   status = list->PushFront(list, &data, 0);
   EXPECT_TRUE(SC_ERROR(status));

   status = list->PushFront(list, NULL, sizeof(int));
   EXPECT_TRUE(SC_ERROR(status));
}


TEST_F(CListEmpty, PushFrontValidPrms)
{
   /*** Arrange ***/
   STATUS_CODE status = SC_SUCCESS;
   void** data = NULL;
   size_t* dataSize = NULL;
   CLIST_NODE* position = NULL;

   /*** Act && Acts ***/
   for (size_t i = 0; i < 25; ++i)
   {
      status = list->PushFront(list, &i, sizeof(size_t));
      ASSERT_FALSE(SC_ERROR(status));
   }

   position = list->Front(list);
   while(position != NULL)
   {
      status = list->GetRefToData(list, position, &data, &dataSize);
      ASSERT_FALSE(SC_ERROR(status));

      position = list->Next(list, position);
   }

   position = list->Front(list);
   while (position != NULL)
   {
      status = list->GetRefToData(list, position, &data, &dataSize);
      ASSERT_FALSE(SC_ERROR(status));

      free(*data);
      *data = malloc(sizeof(double));
      **((double**)data) = 3.141592;
      *dataSize = sizeof(double);

      position = list->Next(list, position);
   }

   position = list->Front(list);
   while (position != NULL)
   {
      status = list->GetRefToData(list, position, &data, &dataSize);
      ASSERT_FALSE(SC_ERROR(status));

      position = list->Next(list, position);
   }
}


// ///////////////////////////////////////////////////////////
// //                         Front                         //
// ///////////////////////////////////////////////////////////

TEST_F(CListEmpty, FrontOnEmpty)
{
   /*** Arrange ***/
   STATUS_CODE status = SC_SUCCESS;

   /*** Act && Assert ***/
   // Invalid params
   CLIST_NODE *head = list->Front(NULL);
   EXPECT_FALSE(SC_ERROR(status));

   // Valid params
   head = list->Front(list);
   EXPECT_TRUE(NULL == head);
}


TEST_F(CListTwentyFiveElement, Front)
{
   /*** Arrange ***/
   STATUS_CODE status = SC_SUCCESS;

   /*** Act && Assert ***/
   // Valid data
   CLIST_NODE* head = list->Front(list);
   EXPECT_TRUE(NULL != head);

   // Invalid data
   int someData;
   head = list->Front((CLIST*)&someData);
   EXPECT_TRUE(NULL == head);
}


// ///////////////////////////////////////////////////////////
// //                     GetRefToData                      //
// ///////////////////////////////////////////////////////////


TEST_F(CListTwentyFiveElement, GetRefToDataInvPrms)
{
   /*** Arrange ***/
   STATUS_CODE status = SC_SUCCESS;
   CLIST_NODE* head = NULL;
   void** data = NULL;
   size_t* dataSize = NULL;

   /*** Act && Assert ***/
   status = list->GetRefToData(NULL, NULL, NULL, NULL);
   EXPECT_TRUE(SC_ERROR(status));

   status = list->GetRefToData(list, NULL, NULL, NULL);
   EXPECT_TRUE(SC_ERROR(status));

   head = list->Front(list);
   ASSERT_TRUE(NULL != head);

   status = list->GetRefToData(list, head, NULL, NULL);
   EXPECT_TRUE(SC_ERROR(status));

   status = list->GetRefToData(list, head, &data, NULL);
   EXPECT_TRUE(SC_ERROR(status));

   status = list->GetRefToData(list, head, NULL, &dataSize);
   EXPECT_TRUE(SC_ERROR(status));
}


TEST_F(CListTwentyFiveElement, GetRefToDataValidPrms)
{
   /*** Arrange ***/
   STATUS_CODE status = SC_SUCCESS;

   /*** Act && Assert ***/
   // Get data
   CLIST_NODE* head = list->Front(list);
   ASSERT_TRUE(NULL != head);
   void** data = NULL;
   size_t *dataSize = NULL;

   status = list->GetRefToData(list, head, &data, &dataSize);
   EXPECT_FALSE(SC_ERROR(status));
   EXPECT_TRUE(24 == **((size_t**)data));
   EXPECT_TRUE(sizeof(size_t) == *dataSize);

   // Change data
   free(*data);

   *data = malloc(sizeof(double));
   **((double**)data) = 3.1415;
   *dataSize = sizeof(double);

   status = list->GetRefToData(list, head, &data, &dataSize);
   EXPECT_FALSE(SC_ERROR(status));
   EXPECT_TRUE(3.1415 == **((double**)data));
   EXPECT_TRUE(sizeof(double) == *dataSize);
}


TEST_F(CListEmpty, InsertAfter)
{
   /*** Arrange ***/
   STATUS_CODE status = SC_SUCCESS;

   /*** Act && Assert ***/
   // Invalid params
   status = list->InsertAfter(NULL, NULL, NULL, 0);
   EXPECT_TRUE(SC_ERROR(status));

   status = list->InsertAfter(list, NULL, NULL, 0);
   EXPECT_TRUE(SC_ERROR(status));

   // Valid params
   size_t data = 0;
   status = list->PushFront(list, &data, sizeof(size_t));
   EXPECT_FALSE(SC_ERROR(status));

   CLIST_NODE* position = list->Front(list);
   ASSERT_FALSE(NULL == position);
   while (data++ != 24)
   {
      status = list->InsertAfter(list, position, &data, sizeof(size_t));
      ASSERT_FALSE(SC_ERROR(status));

      position = list->Next(list, position);
      ASSERT_FALSE(NULL == position);
   }

   position = list->Front(list);
   ASSERT_FALSE(NULL == position);

   size_t  dataSize = 0;
   size_t* receivedData = NULL;
   while (position != NULL)
   {
      status = list->GetCopyData(list, position, (void**)&receivedData, &dataSize);
      ASSERT_FALSE(SC_ERROR(status));

      position = list->Next(list, position);
   }
}


TEST_F(CListEmpty, InsertBefore)
{
   /*** Arrange ***/
   STATUS_CODE status = SC_SUCCESS;

   /*** Act && Assert ***/
   // Invalid params
   status = list->InsertBefore(NULL, NULL, NULL, 0);
   EXPECT_TRUE(SC_ERROR(status));

   status = list->InsertBefore(list, NULL, NULL, 0);
   EXPECT_TRUE(SC_ERROR(status));

   // Valid params
   size_t data = 0;
   status = list->PushFront(list, &data, sizeof(size_t));
   ASSERT_FALSE(SC_ERROR(status));

   CLIST_NODE* position = list->Front(list);
   ASSERT_FALSE(NULL == position);
   while (data++ != 24)
   {
      status = list->InsertBefore(list, position, &data, sizeof(size_t));
      ASSERT_FALSE(SC_ERROR(status));

      position = list->Prev(list, position);
      ASSERT_FALSE(NULL == position);
   }

   position = list->Front(list);
   ASSERT_FALSE(NULL == position);

   size_t  dataSize = 0;
   size_t* receivedData = NULL;
   while (position != NULL)
   {
      status = list->GetCopyData(list, position, (void**)&receivedData, &dataSize);
      ASSERT_FALSE(SC_ERROR(status));

      position = list->Next(list, position);
   }

}


///////////////////////////////////////////////////////////
//                     GetCopyData                       //
///////////////////////////////////////////////////////////

TEST_F(CListTwentyFiveElement, GetCopyData)
{
   /*** Arrange ***/
   STATUS_CODE status = SC_SUCCESS;

   /*** Act && Assert ***/
   // Invalid params
   status = list->GetCopyData(NULL, NULL, NULL, NULL);
   EXPECT_TRUE(SC_ERROR(status));

   // Valid params
   CLIST_NODE *position = list->Front(list);
   ASSERT_TRUE(position != NULL);

   size_t expected = 24;
   while (position != NULL)
   {
      size_t* data = NULL;
      size_t  dataSize = 0;

      status = list->GetCopyData(list, position, (void**)&data, &dataSize);
      ASSERT_FALSE(SC_ERROR(status));
      EXPECT_TRUE(expected == *data);
      EXPECT_TRUE(sizeof(size_t) == dataSize);

      position = list->Next(list, position);
      --expected;
   }
}


///////////////////////////////////////////////////////////
//                      PopFront                         //
///////////////////////////////////////////////////////////

TEST_F(CListTwentyFiveElement, PopFront)
{
   /*** Arrange ***/
   STATUS_CODE status = SC_SUCCESS;

   /*** Act && Assert ***/
   CLIST_NODE* position = list->Front(list);
   ASSERT_FALSE(position == NULL);

   for (size_t i = 1; i <= 5; ++i)
   {
      list->PopFront(list);
      ASSERT_TRUE(25 - i == list->Size(list));
   }

}


TEST_F(CListEmpty, PopFront)
{
   /*** Arrange ***/
   STATUS_CODE status = SC_SUCCESS;

   /*** Act && Assert ***/
   list->PopFront(list);
   ASSERT_TRUE(NULL == list->Front(list));
   ASSERT_TRUE(0 == list->Size(list));

   size_t data = 25;
   status = list->PushFront(list, &data, sizeof(size_t));
   ASSERT_FALSE(SC_ERROR(status));

   ASSERT_FALSE(NULL == list->Front(list));
   ASSERT_TRUE(1 == list->Size(list));

   list->PopFront(list);
   ASSERT_TRUE(0 == list->Size(list));
   ASSERT_TRUE(NULL == list->Front(list));
}


TEST_F(CListEmpty, PopFrontTwoElements)
{
   /*** Arrange ***/
   STATUS_CODE status = SC_SUCCESS;

   /*** Act && Assert ***/
   for (size_t i = 0; i < 2; ++i)
   {
      status = list->PushFront(list, &i, sizeof(size_t));
      ASSERT_FALSE(SC_ERROR(status));
   }

   list->PopFront(list);
   ASSERT_TRUE(1 == list->Size(list));

   CLIST_NODE* head = list->Front(list);
   ASSERT_TRUE(head != NULL);

   size_t* data = NULL;
   size_t dataSize = 0;
   status = list->GetCopyData(list, head, (void**)&data, &dataSize);
   ASSERT_FALSE(SC_ERROR(status));
   ASSERT_TRUE(0 == *data);
   ASSERT_TRUE(sizeof(size_t) == dataSize);
}


TEST_F(CListEmpty, PushBack)
{
   /*** Arrange ***/
   STATUS_CODE status = SC_SUCCESS;

   /*** Act && Assert ***/
   // Invalid params
   status = list->PushBack(NULL, NULL, 0);
   EXPECT_TRUE(SC_ERROR(status));

   status = list->PushBack(list, NULL, 0);
   EXPECT_TRUE(SC_ERROR(status));

   // Valid params
   for (size_t i = 0; i < 25; ++i)
   {
      status = list->PushBack(list, &i, sizeof(size_t));
      ASSERT_FALSE(SC_ERROR(status));
   }

   CLIST_NODE* position = list->Front(list);
   ASSERT_TRUE(NULL != position);
   size_t expected = 0;
   while (position != NULL)
   {
      size_t* data = NULL;
      size_t dataSize = 0;
      status = list->GetCopyData(list, position, (void**)&data, &dataSize);
      ASSERT_FALSE(SC_ERROR(status));
      ASSERT_TRUE(expected == *data);
      ASSERT_TRUE(sizeof(size_t) == dataSize);

      position = list->Next(list, position);
      ++expected;
   }

   expected = 24;
   position = list->Back(list);
   ASSERT_TRUE(NULL != position);
   while (position != NULL)
   {
      size_t* data = NULL;
      size_t dataSize = 0;
      status = list->GetCopyData(list, position, (void**)&data, &dataSize);
      ASSERT_FALSE(SC_ERROR(status));
      ASSERT_TRUE(expected == *data);
      ASSERT_TRUE(sizeof(size_t) == dataSize);

      position = list->Prev(list, position);
      --expected;
   }

}


int main(int argc, char** argv)
{
   ::testing::InitGoogleTest(&argc, argv);

   return RUN_ALL_TESTS();
}