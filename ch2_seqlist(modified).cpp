// ConsoleApplication8.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// Example program
#include "pch.h"
#include <stdio.h>
#include <stdlib.h>

#define maxsize 1000

typedef float datatype;

typedef struct
{
	datatype data[maxsize];
	int last;
}SeqList;

SeqList *init_seqlist()
{
	SeqList *L;
	L = (SeqList*)malloc(sizeof(SeqList));
	L->last = -1;
	return L;
}

int insert_seqlist(SeqList *L, int i, datatype e)
{
	int j;

	if (L->last == maxsize - 1)
	{
		printf("list is already full\n");
		return -1;
	}

	if (i<1 || i>L->last + 2)
	{
		printf("wrong position\n");
		return -1;
	}

	for (j = L->last; j >= i - 1; --j)
	{
		L->data[j + 1] = L->data[j];
	}

	L->data[i - 1] = e;
	L->last++;

	return 1;
}

int delete_seqlist(SeqList *L, int i, datatype e)
{
	int j;
	e = L->data[i - 1];    //记录被删掉的数

	if (i<1 || i>L->last + 2)
	{
		printf("wrong postion\n");
		return -1;
	}

	for (j = L->data[i - 1]; j <= L->last; ++j)
	{
		L->data[j - 1] = L->data[j];
	}
	L->last--;

	return e;    //查看返回值是否为被删的数

}

void print_seqlist(SeqList *L)
{
	int i;
	for (i = 1; i < L->last; ++i)
	{
		printf("%f -> ", L->data[i - 1]);
	}
	printf("%f\n", L->data[L->last]);
}

int main()
{
	int i = 0;

	SeqList* L = init_seqlist();
	for (i = 0; i < 10; ++i)
	{
		insert_seqlist(L, i + 1, i*i);
	}
	printf("list len = %d\n", L->last + 1);

	print_seqlist(L);

	delete_seqlist(L, 3, 0);    //测试函数是否能使用  //e的取值可任意
	print_seqlist(L);    //打印出被删后的顺序表

	return 1;
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
