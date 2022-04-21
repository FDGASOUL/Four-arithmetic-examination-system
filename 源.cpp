#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<windows.h>
#include<string.h>
#include <iostream>
#include <stack>
using namespace std;
struct test {
	char texts[50];
	int result;
	int wrong;
}sql[50];
typedef struct S1				//创建S1栈 
{
	char Char[200];
	int top;
}S1;
typedef struct S2				//创建S2栈 
{
	double num[200];
	int top;
}S2;
class Stack {
private:
	char s2[200];
public:
	Stack(char* s1,int m) {
		Suffix(s1, s2);
		Calculate(s2,m);
	}
	char* GetS2() {
		return s2;
	}
	int Yxj(char);				                    //定义元素优先级 
	int TopYxj(char);				                //定义栈顶元素优先级 
	void cshS1(S1*);				                //对S1栈初始化
	void cshS2(S2*);				                //对S2栈初始化
	int FirstS1(S1*, char);			                //对S1栈进行压栈 
	int FirstS2(S2*, double);	                    //对S2进行压栈
	char TotopS1(S1*);				                //返回栈顶元素 
	char OutS1(S1*);				                //S1出栈 
	double OutS2(S2*);				                //S2出栈 
	void Suffix(char* s1, char* s2);		        //中缀表达式转化为后缀表达式 
	void Calculate(char* s2,int m); 	                    //对后缀表达式进行最终求值 
};
void Stack::cshS1(S1* a)
{
	a->top = -1;
}
void Stack::cshS2(S2* a)
{
	a->top = -1;
}
int Stack::FirstS1(S1* a, char b)
{
	if (a->top < 200)
	{
		a->Char[++a->top] = b;
		return 1;
	}
	else return 0;
}
int Stack::FirstS2(S2* a, double b)
{
	if (a->top < 200)
	{
		a->num[++a->top] = b;
		return 1;
	}
	else return 0;
}
char Stack::TotopS1(S1* a)
{
	return a->Char[a->top];
}
char Stack::OutS1(S1* a)
{
	return a->Char[a->top--];
}
double Stack::OutS2(S2* a)
{
	return a->num[a->top--];
}
int Stack::Yxj(char a)
{
	switch (a)
	{
	case '(': return 6;
	case '*': return 4;
	case '/': return 4;
	case '+': return 2;
	case '-': return 2;
	}
}
int Stack::TopYxj(char a)
{
	switch (a)
	{
	case '(': return 1;
	case '+': return 3;
	case '-': return 3;
	case '*': return 5;
	case '/': return 5;
	}
}
void Stack::Suffix(char* s1, char* s2)
{
	int i = 0, j = 0, F = -1, f = -1;
	S1 B;
	cshS1(&B);
	for (; s1[i] != '\0'; i++)
	{
		if (s1[0] == '-')
		{
			j = strlen(s1);
			for (; j > 0; j--)
			{
				s1[j + 5] = s1[j];
			}
			s1[j++] = '(';
			s1[j++] = '0';
			s1[j++] = '-';
			s1[j++] = '1';
			s1[j++] = ')';
			s1[j] = '*';
		}
		if (s1[i] == '(' && s1[i + 1] == '-')
		{
			j = strlen(s1);
			for (; j > i + 1; j--)
			{
				s1[j + 5] = s1[j];
			}
			s1[j++] = '(';
			s1[j++] = '0';
			s1[j++] = '-';
			s1[j++] = '1';
			s1[j++] = ')';
			s1[j] = '*';
			i = i + 5;
		}
	}
	i = 0;
	j = 0;
	for (; s1[i] != '\0'; i++)
	{
		if (F == 0 && f == 1)
		{
			s2[j++] = ' ';
			F = 1;
		}
		if (s1[i] >= '0' && s1[i] <= '9' || s1[i] == '.')
		{
			s2[j++] = s1[i];
			f = 0;
			F = 0;
		}
		else if (s1[i] == '+' || s1[i] == '-' || s1[i] == '*' || s1[i] == '/' || s1[i] == '(')
		{
			f = 1;
			if (B.top<0 || Yxj(s1[i])>TopYxj(TotopS1(&B)))
			{
				FirstS1(&B, s1[i]);
			}
			else
			{
				for (; B.top >= 0 && Yxj(s1[i]) < TopYxj(TotopS1(&B));)
				{
					s2[j++] = OutS1(&B);
					F = 1;
				}
				if (B.top<0 || Yxj(s1[i])>TopYxj(TotopS1(&B)))
				{
					FirstS1(&B, s1[i]);
				}

			}
		}
		else if (s1[i] == ')')
		{
			f = 1;
			if (TotopS1(&B) != '(')
			{
				F = 1;
			}
			while (TotopS1(&B) != '(')
			{
				s2[j++] = OutS1(&B);
			}
			OutS1(&B);
		}
	}
	for (; B.top >= 0;)
	{
		s2[j++] = OutS1(&B);
	}
	s2[j] = '\0';
}
void Stack::Calculate(char* s1,int m)
{
	int i = 0, f;
	double a, b, sum;
	S2 A;
	cshS2(&A);
	for (; s1[i] != '\0'; i++)
	{
		if (s1[i] == '+' || s1[i] == '-' || s1[i] == '*' || s1[i] == '/')
		{
			a = OutS2(&A);
			b = OutS2(&A);
			if (s1[i] == '+') FirstS2(&A, a + b);
			else if (s1[i] == '-') FirstS2(&A, b - a);
			else if (s1[i] == '*') FirstS2(&A, b * a);
			else if (s1[i] == '/') FirstS2(&A, b / a);
		}
		else
		{
			f = 0;
			sum = 0;
			double divider = 1;
			for (; s1[i] != ' ' && s1[i] != '+' && s1[i] != '-' && s1[i] != '*' && s1[i] != '/'; i++)
			{
				if (s1[i] == '.')
				{
					f = 1;
					i++;
					continue;
				}
				if (f == 0)
				{
					sum = sum * 10 + (double)(s1[i] - '0');
				}
				else
				{
					divider = divider * 10;
					sum = sum + ((double)(s1[i] - '0')) / divider;
				}
			}
			if (s1[i] == '+' || s1[i] == '-' || s1[i] == '*' || s1[i] == '/') i--;
			FirstS2(&A, sum);
		}
	}
	sql[m].result = OutS2(&A);
}
void readPra(int num)
{
	int i = 0;
	FILE* fp = NULL;
	fp = fopen("problem.txt", "r");
	while (i < num)
	{
		fscanf(fp, "%s", sql[i].texts);
		i++;
	}
}
char* Num(int n)
{
	int num;
	num = rand() % n;
	char str[128] = { 0 };
	sprintf_s(str, "%d", num);
	return str;
}
char* Sign1()
{
	int num;
	char i[128];
	num = rand() % 11;
	for (; num > 1;)
	{
		num = rand() % 11;
	}
	if (num == 0)
	{
		strcpy(i, "+");
		return i;
	}
	else if (num == 1)
	{
		strcpy(i, "-");
		return i;
	}
}
char* Sign2()
{

	int num;
	char i[128];
	num = rand() % 11;
	for (; num > 1;)
	{
		num = rand() % 11;
	}
	if (num == 0)
	{
		strcpy(i, "*");
		return i;
	}
	else if (num == 1)
	{
		strcpy(i, "/");
		return i;
	}
}
char* Sign()
{
	int num;
	char i[128];
	num = rand() % 11;
	for (; num > 3;)
	{
		num = rand() % 11;
	}
	if (num == 0)
	{
		strcpy(i, "*");
		return i;
	}
	else if (num == 1)
	{
		strcpy(i, "/");
		return i;
	}
	else if (num == 2)
	{
		strcpy(i, "+");
		return i;
	}
	else if (num == 3)
	{
		strcpy(i, "-");
		return i;
	}
}
int op()
{
	int num;
	num = rand() % 11;
	for (; num > 8;)
	{
		num = rand() % 11;
	}
	return num;
}
void Random(int n,int nums)
{
	int num, i = 0;
	char str[128];
	srand(time(NULL));
	for (i = 0; i < nums; i++)
	{
		num = op();
		switch (num)
		{
			char e0[128], e1[128], e2[128], e3[128], e4[128], e5[128], e6[128], e7[128], e8[128], e9[128];
			int j, flag;
		case 0:
			strcpy(e0, "(");
			strcpy(e1, Num(n));
			strcpy(e2, Sign1());
			strcpy(e3, Num(n));
			strcpy(e4, ")");
			strcpy(e5, Sign2());
			strcpy(e6, Num(n));
			strcpy(e7, Sign());
			strcpy(e8, Num(n));
			strcpy(e9, "=");
			strcat(e8, e9);
			strcat(e7, e8);
			strcat(e6, e7);
			strcat(e5, e6);
			strcat(e4, e5);
			strcat(e3, e4);
			strcat(e2, e3);
			strcat(e1, e2);
			strcat(e0, e1);
			j = 0;
			flag = 0;
			for (j = 0; e0[j + 1] != '\0'; j++)
			{
				if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
			}
			if (flag == 1)
			{
				i--;
				continue;
			}
			strcpy(sql[i].texts, e0);
			continue;
		case 1:
			strcpy(e0, "(");
			strcpy(e1, Num(n));
			strcpy(e2, Sign1());
			strcpy(e3, Num(n));
			strcpy(e4, ")");
			strcpy(e5, Sign());
			strcpy(e6, Num(n));
			strcpy(e7, "=");
			strcat(e6, e7);
			strcat(e5, e6);
			strcat(e4, e5);
			strcat(e3, e4);
			strcat(e2, e3);
			strcat(e1, e2);
			strcat(e0, e1);
			j = 0;
			flag = 0;
			for (j = 0; e0[j + 1] != '\0'; j++)
			{
				if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
			}
			if (flag == 1)
			{
				i--;
				continue;
			}
			strcpy(sql[i].texts, e0);
			continue;
		case 2:
			strcpy(e0, Num(n));
			strcpy(e1, Sign());
			strcpy(e2, "(");
			strcpy(e3, Num(n));
			strcpy(e4, Sign1());
			strcpy(e5, Num(n));
			strcpy(e6, ")");
			strcpy(e7, Sign());
			strcpy(e8, Num(n));
			strcpy(e9, "=");
			strcat(e8, e9);
			strcat(e7, e8);
			strcat(e6, e7);
			strcat(e5, e6);
			strcat(e4, e5);
			strcat(e3, e4);
			strcat(e2, e3);
			strcat(e1, e2);
			strcat(e0, e1);
			j = 0;
			flag = 0;
			for (j = 0; e0[j + 1] != '\0'; j++)
			{
				if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
			}
			if (flag == 1)
			{
				i--;
				continue;
			}
			strcpy(sql[i].texts, e0);
			continue;
		case 3:
			strcpy(e0, Num(n));
			strcpy(e1, Sign2());
			strcpy(e2, Num(n));
			strcpy(e3, Sign1());
			strcpy(e4, Num(n));
			strcpy(e5, Sign2());
			strcpy(e6, Num(n));
			strcpy(e7, "=");
			strcat(e6, e7);
			strcat(e5, e6);
			strcat(e4, e5);
			strcat(e3, e4);
			strcat(e2, e3);
			strcat(e1, e2);
			strcat(e0, e1);
			j = 0;
			flag = 0;
			for (j = 0; e0[j + 1] != '\0'; j++)
			{
				if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
			}
			if (flag == 1)
			{
				i--;
				continue;
			}
			strcpy(sql[i].texts, e0);
			continue;
		case 4:
			strcpy(e0, Num(n));
			strcpy(e1, Sign());
			strcpy(e2, Num(n));
			strcpy(e3, Sign2());
			strcpy(e4, "(");
			strcpy(e5, Num(n));
			strcpy(e6, Sign1());
			strcpy(e7, Num(n));
			strcpy(e8, ")");
			strcpy(e9, "=");
			strcat(e8, e9);
			strcat(e7, e8);
			strcat(e6, e7);
			strcat(e5, e6);
			strcat(e4, e5);
			strcat(e3, e4);
			strcat(e2, e3);
			strcat(e1, e2);
			strcat(e0, e1);
			j = 0;
			flag = 0;
			for (j = 0; e0[j + 1] != '\0'; j++)
			{
				if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
			}
			if (flag == 1)
			{
				i--;
				continue;
			}
			strcpy(sql[i].texts, e0);
			continue;
		case 5:
			strcpy(e0, Num(n));
			strcpy(e1, Sign1());
			strcpy(e2, Num(n));
			strcpy(e3, Sign2());
			strcpy(e4, Num(n));
			strcpy(e5, Sign1());
			strcpy(e6, Num(n));
			strcpy(e7, "=");
			strcat(e6, e7);
			strcat(e5, e6);
			strcat(e4, e5);
			strcat(e3, e4);
			strcat(e2, e3);
			strcat(e1, e2);
			strcat(e0, e1);
			j = 0;
			flag = 0;
			for (j = 0; e0[j + 1] != '\0'; j++)
			{
				if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
			}
			if (flag == 1)
			{
				i--;
				continue;
			}
			strcpy(sql[i].texts, e0);
			continue;
		case 6:
			strcpy(e0, Num(n));
			strcpy(e1, Sign2());
			strcpy(e2, "(");
			strcpy(e3, Num(n));
			strcpy(e4, Sign());
			strcpy(e5, Num(n));
			strcpy(e6, Sign());
			strcpy(e7, Num(n));
			strcpy(e8, ")");
			strcpy(e9, "=");
			strcat(e8, e9);
			strcat(e7, e8);
			strcat(e6, e7);
			strcat(e5, e6);
			strcat(e4, e5);
			strcat(e3, e4);
			strcat(e2, e3);
			strcat(e1, e2);
			strcat(e0, e1);
			j = 0;
			flag = 0;
			for (j = 0; e0[j + 1] != '\0'; j++)
			{
				if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
			}
			if (flag == 1)
			{
				i--;
				continue;
			}
			strcpy(sql[i].texts, e0);
			continue;
		case 7:
			strcpy(e0, "(");
			strcpy(e1, Num(n));
			strcpy(e2, Sign());
			strcpy(e3, Num(n));
			strcpy(e4, Sign());
			strcpy(e5, Num(n));
			strcpy(e6, ")");
			strcpy(e7, Sign2());
			strcpy(e8, Num(n));
			strcpy(e9, "=");
			strcat(e8, e9);
			strcat(e7, e8);
			strcat(e6, e7);
			strcat(e5, e6);
			strcat(e4, e5);
			strcat(e3, e4);
			strcat(e2, e3);
			strcat(e1, e2);
			strcat(e0, e1);
			j = 0;
			flag = 0;
			for (j = 0; e0[j + 1] != '\0'; j++)
			{
				if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
			}
			if (flag == 1)
			{
				i--;
				continue;
			}
			strcpy(sql[i].texts, e0);
			continue;
		case 8:
			strcpy(e0, Num(n));
			strcpy(e1, Sign1());
			strcpy(e2, Num(n));
			strcpy(e3, Sign2());
			strcpy(e4, Num(n));
			strcpy(e5, "=");
			strcat(e4, e5);
			strcat(e3, e4);
			strcat(e2, e3);
			strcat(e1, e2);
			strcat(e0, e1);
			j = 0;
			flag = 0;
			for (j = 0; e0[j + 1] != '\0'; j++)
			{
				if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
			}
			if (flag == 1)
			{
				i--;
				continue;
			}
			strcpy(sql[i].texts, e0);
			continue;
		}
	}
}
void Practice(int n)
{
	int num, i = 0,m=0,p,f;
	char str[128];
	srand(time(NULL));
	for (;m==0;)
	{
			num = op();
			switch (num)
			{
				char e0[128], e1[128], e2[128], e3[128], e4[128], e5[128], e6[128], e7[128], e8[128], e9[128];
				int j, flag;
			case 0:
				strcpy(e0, "(");
				strcpy(e1, Num(n));
				strcpy(e2, Sign1());
				strcpy(e3, Num(n));
				strcpy(e4, ")");
				strcpy(e5, Sign2());
				strcpy(e6, Num(n));
				strcpy(e7, Sign());
				strcpy(e8, Num(n));
				strcpy(e9, "=");
				strcat(e8, e9);
				strcat(e7, e8);
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				break;
			case 1:
				strcpy(e0, "(");
				strcpy(e1, Num(n));
				strcpy(e2, Sign1());
				strcpy(e3, Num(n));
				strcpy(e4, ")");
				strcpy(e5, Sign());
				strcpy(e6, Num(n));
				strcpy(e7, "=");
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				break;
			case 2:
				strcpy(e0, Num(n));
				strcpy(e1, Sign());
				strcpy(e2, "(");
				strcpy(e3, Num(n));
				strcpy(e4, Sign1());
				strcpy(e5, Num(n));
				strcpy(e6, ")");
				strcpy(e7, Sign());
				strcpy(e8, Num(n));
				strcpy(e9, "=");
				strcat(e8, e9);
				strcat(e7, e8);
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				break;
			case 3:
				strcpy(e0, Num(n));
				strcpy(e1, Sign2());
				strcpy(e2, Num(n));
				strcpy(e3, Sign1());
				strcpy(e4, Num(n));
				strcpy(e5, Sign2());
				strcpy(e6, Num(n));
				strcpy(e7, "=");
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				break;
			case 4:
				strcpy(e0, Num(n));
				strcpy(e1, Sign());
				strcpy(e2, Num(n));
				strcpy(e3, Sign2());
				strcpy(e4, "(");
				strcpy(e5, Num(n));
				strcpy(e6, Sign1());
				strcpy(e7, Num(n));
				strcpy(e8, ")");
				strcpy(e9, "=");
				strcat(e8, e9);
				strcat(e7, e8);
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				break;
			case 5:
				strcpy(e0, Num(n));
				strcpy(e1, Sign1());
				strcpy(e2, Num(n));
				strcpy(e3, Sign2());
				strcpy(e4, Num(n));
				strcpy(e5, Sign1());
				strcpy(e6, Num(n));
				strcpy(e7, "=");
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				break;
			case 6:
				strcpy(e0, Num(n));
				strcpy(e1, Sign2());
				strcpy(e2, "(");
				strcpy(e3, Num(n));
				strcpy(e4, Sign());
				strcpy(e5, Num(n));
				strcpy(e6, Sign());
				strcpy(e7, Num(n));
				strcpy(e8, ")");
				strcpy(e9, "=");
				strcat(e8, e9);
				strcat(e7, e8);
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				break;
			case 7:
				strcpy(e0, "(");
				strcpy(e1, Num(n));
				strcpy(e2, Sign());
				strcpy(e3, Num(n));
				strcpy(e4, Sign());
				strcpy(e5, Num(n));
				strcpy(e6, ")");
				strcpy(e7, Sign2());
				strcpy(e8, Num(n));
				strcpy(e9, "=");
				strcat(e8, e9);
				strcat(e7, e8);
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				break;
			case 8:
				strcpy(e0, Num(n));
				strcpy(e1, Sign1());
				strcpy(e2, Num(n));
				strcpy(e3, Sign2());
				strcpy(e4, Num(n));
				strcpy(e5, "=");
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				break;
			}
			printf("%s", sql[i].texts);
			Stack A(sql[i].texts, i);
			scanf("%d", &f);
			if (sql[i].result == f)
			{
				printf("答案正确\n");
			}
			else
			{
				printf("答案错误\n");
				printf("正确答案为：%d\n", sql[i].result);
			}
		
		printf("是否继续练习\n");
		printf("----------------\n");
		printf("1.是\n2.否\n");
		printf("----------------\n");
		scanf("%d", &p);
		system("cls");
		while (p != 1 && p != 2)
		{
			printf("选择错误，请重新选择：");
			scanf("%d", &p);
		}
		system("cls");
		if (p == 2)
		{
			m = 1;
		}
	}
}
void Answer(int num)
{
	int m;
	
	for (m = 0; m < num; m++)
	{
		Stack A(sql[m].texts,m);
	}
}
int userAnswer(int num)
{
	int i,j,m;
	FILE* fp;
	double p,q, trueNum = 0;
	q = num;
	int result;
	for (i=0;i<50;i++)
	{
		sql[i].wrong = 0;
	}
	for (i = 0; i < num; i++)
	{
		printf("第%i道题目：%s", i + 1, sql[i].texts);
		scanf("%d", &result);
		if (result == sql[i].result)
			trueNum++;
		else
		{
			sql[i].wrong = 1;
		}
	}
	p = trueNum / q*100;
	printf("您一共答对了%.0lf道题目，正确率为%.0lf%%\n", trueNum,p);
	fp = fopen("上次成绩.txt", "r");
	fscanf(fp, "%d", &m);
	fclose(fp);
	fp = fopen("替换.txt", "w+");
	fclose(fp);
	remove("上次成绩.txt");
	rename("替换.txt", "上次成绩.txt");
	fp = fopen("上次成绩.txt", "a");
	fprintf(fp, "%.0lf", p);
	fclose(fp);
	fp = fopen("历史成绩.txt", "a");
	fprintf(fp, "%.0lf\n",trueNum);
	fclose(fp);
	if (m < p)
	{
		printf("----------------\n");
		printf("您上次测试正确率为%d%%\n",m);
		printf("恭喜你进步了！\n");
		printf("----------------\n");
	}
	else if (m > p)
	{
		printf("----------------\n");
		printf("您上次测试正确率为%d%%\n", m);
		printf("退步了哦，请继续努力。\n");
		printf("----------------\n");
	}
	else
	{
		printf("----------------\n");
		printf("您上次测试正确率为%d%%\n", m);
		printf("跟上次取得了一样的成绩呢。\n");
		printf("----------------\n");
	}
	for (i = 0; i < num; i++)
	{
		if (sql[i].wrong == 1)
		{
			fp = fopen("错题本.txt", "a");
			fprintf(fp, "%s%d\n", sql[i].texts,sql[i].result);
			fclose(fp);
		}
	}
	printf("错误题目已经保存到错题本。\n");
	printf("是否查看错题？\n");
	printf("----------------\n");
	printf("1.是\n2.否\n");
	printf("----------------\n");
	scanf("%d", &j);
	while (j != 1 && j != 2 )
	{
		printf("选择错误，请重新选择：");
		scanf("%d", &j);
	}
	if (j == 1)
	{
		printf("以下为错误题目\n");
		for (i = 0; i < 50; i++)
		{
			if (sql[i].wrong==1)
			{
				printf("%s%d\n",sql[i].texts,sql[i].result);
			}
		}
		system("pause");
	}
	return 0;
}
int main()
{
	int s=0,t,i,His,num;
	FILE* fp;
	char Wro[100];
	for (; s == 0;)
	{
		printf("欢迎使用小学生四则运算练习及考试系统\n");
		printf("请选择题目难度：\n");
		printf("----------------\n");
		printf("1.10以内\n2.100以内\n3.1000以内\n");
		printf("----------------\n");
		int a, b, c, m, n;
		scanf("%d", &a);
		system("cls");
		while (a != 1 && a != 2 && a != 3)
		{
			printf("选择错误，请重新选择：");
			scanf("%d", &a);
		}
		system("cls");
		if (a == 1)
		{
			n = 11;
			printf("请选择考试或练习：\n");
			printf("----------------\n");
			printf("1.考试\n2.练习\n3.错题本\n4.历史成绩\n");
			printf("----------------\n");
			scanf("%d", &b);
			system("cls");
			while (b != 1 && b != 2&& b!=3&&b!=4)
			{
				printf("选择错误，请重新选择：");
				scanf("%d", &b);
			}
			system("cls");
			if (b == 1)
			{
				printf("请选择考试方式：\n");
				printf("----------------\n");
				printf("1.系统随机出题\n2.导入题目\n");
				printf("----------------\n");
				scanf("%d", &c);
				system("cls");
				while (c != 1 && c != 2)
				{
					printf("选择错误，请重新选择：");
					scanf("%d", &c);
				}
				system("cls");
				if (c == 1)
				{
					printf("请选择考试题目数量：\n");
					scanf("%d", &num);
					Random(n,num);
					Answer(num);
					userAnswer(num);
				}
				else if (c == 2)
				{
					printf("请选择考试题目数量：\n");
					scanf("%d", &num);
					readPra(num);
					Answer(num);
					userAnswer(num);
				}
			}
			else if (b == 2)
			{
				Practice(n);
			}
			else if (b == 3)
			{
				printf("以下为你曾经做错的题目。\n");
				fp = fopen("错题本.txt", "r");
				while (!feof(fp))
				{
					fscanf(fp, "%s", &Wro);
					printf("%s", Wro);
					printf("\n");
				}
				fclose(fp);
				system("pause");
			}
			else if (b == 4)
			{
				fp = fopen("历史成绩.txt", "r");
				while (!feof(fp))
				{
					fscanf(fp, "%d", &His);
					printf("做对了%d道题\n", His);
					printf("----------------\n");
				}
				fclose(fp);
				system("pause");
			}
		}
		else if (a == 2)
		{
			n = 101;
			printf("请选择考试或练习：\n");
			printf("----------------\n");
			printf("1.考试\n2.练习\n3.错题本\n4.历史成绩\n");
			printf("----------------\n");
			scanf("%d", &b);
			system("cls");
			while (b != 1 && b != 2 && b != 3 && b != 4)
			{
				printf("选择错误，请重新选择：");
				scanf("%d", &b);
			}
			system("cls");
			if (b == 1)
			{
				printf("请选择考试方式：\n");
				printf("----------------\n");
				printf("1.系统随机出题\n2.导入题目\n");
				printf("----------------\n");
				scanf("%d", &c);
				system("cls");
				while (c != 1 && c != 2)
				{
					printf("选择错误，请重新选择：");
					scanf("%d", &c);
				}
				system("cls");
				if (c == 1)
				{
					printf("请选择考试题目数量：\n");
					scanf("%d", &num);
					Random(n, num);
					Answer(num);
					userAnswer(num);
				}
				else if (c == 2)
				{
					printf("请选择考试题目数量：\n");
					scanf("%d", &num);
					readPra(num);
					Answer(num);
					userAnswer(num);
				}
			}
			else if (b == 2)
			{
				Practice(n);
			}
			else if (b == 3)
			{
				printf("以下为你曾经做错的题目。\n");
				fp = fopen("错题本.txt", "r");
				while (!feof(fp))
				{
					fscanf(fp, "%s", &Wro);
					printf("%s", Wro);
					printf("\n");
				}
				fclose(fp);
				system("pause");
			}
			else if (b == 4)
			{
				fp = fopen("历史成绩.txt", "r");
				while (!feof(fp))
				{
					fscanf(fp, "%d", &His);
					printf("做对了%d道题\n", His);
					printf("----------------\n");
				}
				fclose(fp);
				system("pause");
			}
		}
		else if (a == 3)
		{
			n = 1001;
			printf("请选择考试或练习：\n");
			printf("----------------\n");
			printf("1.考试\n2.练习\n3.错题本\n4.历史成绩\n");
			printf("----------------\n");
			scanf("%d", &b);
			system("cls");
			while (b != 1 && b != 2 && b != 3 && b != 4)
			{
				printf("选择错误，请重新选择：");
				scanf("%d", &b);
			}
			system("cls");
			if (b == 1)
			{
				printf("请选择考试方式：\n");
				printf("----------------\n");
				printf("1.系统随机出题\n2.导入题目\n");
				printf("----------------\n");
				scanf("%d", &c);
				system("cls");
				while (c != 1 && c != 2)
				{
					printf("选择错误，请重新选择：");
					scanf("%d", &c);
				}
				system("cls");
				if (c == 1)
				{
					printf("请选择考试题目数量：\n");
					scanf("%d", &num);
					Random(n, num);
					Answer(num);
					userAnswer(num);
				}
				else if (c == 2)
				{
					printf("请选择考试题目数量：\n");
					scanf("%d", &num);
					readPra(num);
					Answer(num);
					userAnswer(num);
				}
			}
			else if (b == 2)
			{
				Practice(n);
			}
			else if (b == 3)
			{
				printf("以下为你曾经做错的题目。\n");
				fp = fopen("错题本.txt", "r");
				while (!feof(fp))
				{
					fscanf(fp, "%s", &Wro);
					printf("%s", Wro);
					printf("\n");
				}
				fclose(fp);
				system("pause");
			}
			else if (b == 4)
			{
				fp = fopen("历史成绩.txt", "r");
				while (!feof(fp))
				{
					fscanf(fp, "%d", &His);
					printf("做对了%d道题\n", His);
					printf("----------------\n");
				}
				fclose(fp);
				system("pause");
			}
		}
		system("cls");
		printf("是否继续使用\n");
		printf("----------------\n");
		printf("1.是    2.否\n");
		printf("----------------\n");
		scanf("%d", &t);
		system("cls");
		while (t != 1 && t != 2)
		{
			printf("选择错误，请重新选择：");
			scanf("%d", &t);
		}
		if (t == 2)
			s = 1;
	}
}