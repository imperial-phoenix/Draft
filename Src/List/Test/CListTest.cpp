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


struct CListOneElement : public testing::Test
{
   CLIST* list = NULL;

   // Per-test set-up
   void SetUp() override
   {
      list = CListCreate();
      ASSERT_FALSE(list == NULL);

      int data = 1;
      STATUS_CODE status = list->PushFront(list, &data, sizeof(int));
      ASSERT_FALSE(SC_ERROR(status));
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

      std::printf("data: %ld\n", **((size_t**)data));

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

      std::printf("data %lf\n", **((double**)data));

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


TEST_F(CListOneElement, Front)
{
   /*** Arrange ***/
   STATUS_CODE status = SC_SUCCESS;

   /*** Act ***/
   CLIST_NODE* head = list->Front(list);

   /*** Assert ***/
   EXPECT_TRUE(NULL != head);
}


// ///////////////////////////////////////////////////////////
// //                     GetRefToData                      //
// ///////////////////////////////////////////////////////////


TEST_F(CListOneElement, GetRefToDataInvPrms)
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


TEST_F(CListOneElement, GetRefToDataValidPrms)
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
   EXPECT_TRUE(1 == **((int**)data));
   EXPECT_TRUE(sizeof(int) == *dataSize);

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


///////////////////////////////////////////////////////////
//                         Front                         //
///////////////////////////////////////////////////////////



int main(int argc, char** argv)
{
   ::testing::InitGoogleTest(&argc, argv);

   return RUN_ALL_TESTS();
}