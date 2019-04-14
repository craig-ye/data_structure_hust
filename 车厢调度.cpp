// ConsoleApplication18.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <stdio.h>
#define maxsize n
#define n 3
typedef int Elemtype;

struct Snode
{
	Elemtype data[maxsize];
	Elemtype top;
}S;

void Initstack()
{
	S.top = -1;
}

void push(Elemtype x)
{
	S.top++;
	S.data[S.top] = x;
}

int pop()
{
	int temp;
	temp = S.data[S.top];
	S.top--;
	return temp;
}

int Emptystack()
{
	if (S.top == -1)
	{
		return 1;
	}
	else return 0;
}

void Arrange(int position, int path[], int curposition)
{
	int m, i;
	if (position < n)
	{
		push(position + 1);
		Arrange(position + 1, path, curposition);
		pop();
	}

	if (!Emptystack())
	{
		m = pop();
		path[curposition] = m;
		Arrange(position, path, ++curposition);
		push(m);
	}

	if (position == n && Emptystack())
	{
		for (i = 0; i < curposition; i++)
		{
			printf("%3d", path[i]);
		}
		printf("\n");
	}
}
void main()
{
	int path[maxsize];
	Initstack();
	push(1);
	printf("可能的输出序列为：\n");
	Arrange(1, path, 0);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
