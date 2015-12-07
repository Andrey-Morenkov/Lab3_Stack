#pragma once
// ������������ ��������� ������ - ���������� ���������

#include <iostream>
#include "TStack.h"
#include <string.h>
using namespace std;

const int MaxLen = 201; // 200 + \0

class TParcer
{
private:

	char inf[MaxLen];    // ���������   �����
	char post[MaxLen];   // ����������� �����
	TStack<double> st_d; // ���� ��� �����
	TStack<char> st_c;   // ���� ��� �������� ��������


	int Priority(char ch);                     // ����������� ����������� ��������
	bool IsOperation(char ch);                 // ��������?
	bool IsNumber(char ch);                    // �����?

public:

	TParcer (char *s = NULL ) : st_d(100), st_c(100)
	{
		if ( s == NULL)
			inf[0] = '\0';
		else
			strcpy (inf, s);
	}

	~TParcer()
	{
	}

	bool CheckBrace(char* str);                // �������� ������
	void ClearStacks();                        // �������� ����� (���������)
	void InfToPost();                          // ������� �� ������� ������ � �����������
	double CalcPost();                         // ��������� �����������
	double Calc();                             // ����������� ���������
	double ExNumber(const char *s, int& len);  // �������� ����� ������ 1 �������
};//----------------------------------------------------------------------------------------------------------------------------

int TParcer:: Priority(char ch)
{
	int n;
	switch (ch)
	{
	case '(' :           ;
	case ')' : n=0; break;
	case '+':            ;
	case '-':  n=1; break;
    case '*':            ;
	case '/':  n=2; break;
 	case '^':  n=3; break;   
	default :  n=-1;break;
	}
	return n;
}/*-------------------------------------------------------------------------*/

bool TParcer::IsOperation(char ch)
{
	if ((ch == '+') || (ch == '-') || (ch == '*') || (ch == '/') || (ch == '^'))
		return true;
	else
		return false;
}/*-------------------------------------------------------------------------*/

bool TParcer::IsNumber(char ch)
{
	if ((!IsOperation(ch)) && (ch != '(') && (ch != ')'))
		return true;
	else
		return false;
}/*-------------------------------------------------------------------------*/

void TParcer::ClearStacks()
{
	st_d.Clear();
	st_c.Clear();
}/*-------------------------------------------------------------------------*/

void TParcer::InfToPost()
{
	ClearStacks();
	int i = 0;
	int j = 0;
	st_c.Push('=');     //��������� �������

	while ( inf[i] != '\0')
	{
		if (IsNumber (inf[i]))
		{
			post[j] = inf[i];
			j++;
		}
		else
		{
			if (inf [i] == '(')
				st_c.Push(inf[i]);
			else
				if (inf[i] == ')')
				{
					char tmp = st_c.Pop();
					while (tmp != '(')
					{
						post[j] = tmp;
						j++;
						tmp = st_c.Pop();
					}
				}
				else
					if (IsOperation (inf[i]))
					{
						char tmp = st_c.Pop();
						while ((Priority(tmp) >= Priority (inf[i])))
						{
							post[j] = tmp;
							j++;
							tmp = st_c.Pop();
						}
						st_c.Push(tmp);
						st_c.Push(inf[i]);
					}
		}
		i++;
	}
}/*-------------------------------------------------------------------------*/

bool TParcer::CheckBrace(char* str)
{
	TStack <char> s(200);
	int i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '(')
			s.Push(str[i]);
		if (str[i] == ')')
		{
			if (s.IsEmpty())
				return false;
			s.Pop();
		}
		i++;
	}
	return s.IsEmpty();
}/*-------------------------------------------------------------------------*/

double TParcer::CalcPost()
{
	int i = 0;
	st_d.Clear();

	while ((post[i] != '\0')&&(post[i] != '='))
	{
		if (IsNumber(post[i]))
			st_d.Push (post[i] - '0');                        // �������� ��� ���� ����� ���� ����� � �� ������
		if (IsOperation (post[i]))
		{
			double op1,op2;
			op2 = st_d.Pop();
			op1 = st_d.Pop();
			switch (post[i])
			{
			case '+': st_d.Push (op1 + op2); break;
			case '-': st_d.Push (op1 - op2); break;
			case '*': st_d.Push (op1 * op2); break;
			case '/': st_d.Push (op1 / op2); break;
			}
		}
		i++;
	}
	double tmp = st_d.Pop();
	if (st_d.IsEmpty())
		return tmp;
	else
		throw st_d.Pop();
}/*-------------------------------------------------------------------------*/

double TParcer::ExNumber(const char *s, int& len)  
{
	double tmp = atof(s); // �������� ������ � int
	int i = 0;

	while (s[i] != '\0')
	if (IsNumber(s[i]))
		i++;
	else break;
	len = i;
	return tmp;
}/*-------------------------------------------------------------------------*/

double TParcer::Calc()
{
	ClearStacks();
	int i   = 0;
	int len = 0;

	st_c.Push('=');     //��������� �������	
	if(!CheckBrace(inf))
		throw '(';

	while (inf[i] != '\0')
	{
		if (IsNumber (inf[i]))
		{
			double tmp = ExNumber (&inf[i],len);
			st_d.Push(tmp);
			i= i+len-1;
		}
		else
		{
			if (inf[i] == '(')
				st_c.Push(inf[i]);
			else
				if (inf[i] == ')')
				{
					char tmpc = st_c.Pop();
					while (tmpc != '(')
					{
						double op2 = st_d.Pop();
						double op1 = st_d.Pop();
						switch (tmpc)
						{
						case '+': st_d.Push (op1 + op2);    break;
			            case '-': st_d.Push (op1 - op2);    break;
			            case '*': st_d.Push (op1 * op2);    break;
		 	            case '/': st_d.Push (op1 / op2);    break;
			            case '^': st_d.Push (pow(op1,op2)); break; 
						}
						tmpc = st_c.Pop();
					}
				}
				else
					if (IsOperation(inf[i]))
					{
						char tmp = st_c.Pop();
						while (Priority(tmp) >= Priority(inf[i]))
						{
							double op2 = st_d.Pop();
							double op1 = st_d.Pop();
							switch (tmp)
						    {
						    case '+': st_d.Push (op1 + op2);    break;
			                case '-': st_d.Push (op1 - op2);    break;
			                case '*': st_d.Push (op1 * op2);    break;
		 	                case '/': st_d.Push (op1 / op2);    break;
			                case '^': st_d.Push (pow(op1,op2)); break; 
						    }
							tmp = st_c.Pop();
						}
						st_c.Push(tmp);
						st_c.Push(inf[i]);
					}
		}
		i++;
	}
	char tmp = st_c.Pop();
	while (tmp != '=')
	{
		double op2 = st_d.Pop();
		double op1 = st_d.Pop();
		switch (tmp)
		{
	       case '+': st_d.Push (op1 + op2);    break;
	       case '-': st_d.Push (op1 - op2);    break;
	       case '*': st_d.Push (op1 * op2);    break;
	       case '/': st_d.Push (op1 / op2);    break;
	       case '^': st_d.Push (pow(op1,op2)); break; 
		}
		tmp = st_c.Pop();
	}
    return st_d.Pop();
}/*-------------------------------------------------------------------------*/