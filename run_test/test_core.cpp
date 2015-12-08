#include "..\Lab3_Stack\TStack.h"

#include "..\gtest\gtest.h"

TEST(TStack, Can_Create_Stack)
{
  ASSERT_NO_THROW(TStack<int> s(5));
}