/**
 * @file  CListTest.cpp
 * @brief Unit Tests for CLIST
 */

#include "gtest/gtest.h"

extern "C"
{
   #include "Include/CList.h"
}


TEST(CListTest, CListCreate)
{
   // Arrange
   CLIST* list = NULL;

   // Act
   list = CListCreate();

   // Assert
   ASSERT_FALSE(list == NULL);
}


int main(int argc, char** argv)
{
   ::testing::InitGoogleTest(&argc, argv);

   return RUN_ALL_TESTS();
}