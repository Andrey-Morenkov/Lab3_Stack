// Lab3_Stack.cpp: ���������� ����� ����� ��� ����������� ����������.

#include "stdafx.h"
#include "TStack.h"
#include "TParcer.h"
#include <iostream>
#include <string>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	char str[200];
	TStack<int> s; // ����
	for(;;)
	{
	    cout<<"Input: "<<endl;
	    gets(str);
	   	TParcer p(str);
    	double b = p.Calc();
    	printf("= %lf\n",b);
		cout<<endl;
 	}
	return 0;
}

