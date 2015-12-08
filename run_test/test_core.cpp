#include "..\Lab3_Stack\TStack.h"
#include "..\Lab3_Stack\TParcer.h"

#include "..\gtest\gtest.h"

TEST(TStack, Can_Create_Stack)
{
  ASSERT_NO_THROW(TStack<int> s(5));
}
TEST(TParcer, Can_Create_Parcer)
{
  ASSERT_NO_THROW(TParcer s);
}
TEST(TStack, Cant_Create_Stack_too_big_size)
{
  ASSERT_ANY_THROW(TStack<int> s(MaxStackSize+1));
}
TEST(TStack, Cant_Pop_From_Empty_Stack)
{
	TStack<int> s(1);
	ASSERT_ANY_THROW(s.Pop());
}