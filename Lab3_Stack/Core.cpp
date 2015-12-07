// Lab3_Stack.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "TStack.h"
#include "TParcer.h"
#include <iostream>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	TStack<int> s;
	char* a="5^24"; //= 20
	TParcer p(a);
	double b = p.Calc();
	printf("%lf",b);
	return 0;
}

