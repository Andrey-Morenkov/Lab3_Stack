#include "..\Lab3_Stack\TStack.h"
#include "..\Lab3_Stack\TParcer.h"

#include "..\gtest\gtest.h"
#include <iostream>
#include <string>

TEST(TStack, Can_Create_Stack)
{
  ASSERT_NO_THROW(TStack<int> s(5));
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
TEST(TStack, Cant_Push_to_Full_Stack)
{
	TStack<int> s(1);
	s.Push(1);
	ASSERT_ANY_THROW(s.Push(1));
}
TEST(TStack, Can_See_Top_of_Stack)
{
	TStack<int> s(10);
	s.Push(5);
	EXPECT_EQ(s.Top(),5);
}
TEST(TParcer, Can_Create_Parcer)
{
	ASSERT_NO_THROW(TParcer s);
}
TEST(TParcer, Can_Calculate)
{
	char str[13];
	str[0] = '1';
	str[1] = '+';   // 1+(2^4-8)*3/7 = 31/7 ~4.4285
	str[2] = '(';
	str[3] = '2';
	str[4] = '^';
	str[5] = '4';
	str[6] = '-';
	str[7] = '8';
	str[8] = ')';
	str[9] = '*';
	str[10] = '3';
	str[11] = '/';
	str[12] = '7';
	TParcer p(str);
	double b = p.Calc();
	double b1 = 31.0 / 7.0;
	EXPECT_EQ(b1,b);
}

TEST(TParcer, Can_Detect_Wrong_Brackets)
{
	char str[10];
	str[0] = '1';
	str[1] = '+';
	str[2] = '(';
	str[3] = ')';
	str[4] = ')';
	str[5] = '3';
	TParcer p(str);
	EXPECT_EQ(false, p.CheckBrace(str));
}