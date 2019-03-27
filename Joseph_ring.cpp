// ConsoleApplication17.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <stdio.h>
#include <malloc.h>
using namespace std;

typedef struct Lnode {
	int number;		//成员编号
	int password;		//成员密码
	struct Lnode *next;		//指向下一个的指针
}Lnode, *looplist;

void Initlooplist(looplist &L, int n)
//按编号输入各成员的密码值，建立单链表L，再使表尾指向表头，形成循环链表
{
	L = (looplist)malloc(sizeof(Lnode));
	looplist head = (looplist)malloc(sizeof(Lnode));
	head->next = L;
	for (int i = 0; i < n; i++)
	{
		looplist p = (looplist)malloc(sizeof(Lnode));		//生成新结点
		scanf_s("%d",&p->password);		//输入每个人的密码

		if (p->password <= 0);
		{
			printf("密码需为正");		//报错
			return -1;
		}

		p->number = i + 1;		//记下每个人的编号
		L->next = p;		//指向新结点
		L = L->next;		//移动L的位置
	}
	L->next = head->next->next;		//表尾指向表头
}

void Josephring(looplist L, int m, int n)
//循环链表找到每次m对应的结点，读取数据后释放
{
	looplist p = (looplist)malloc(sizeof(Lnode));		//创建新结点
	p = L;
	for (int i = 0; i < n; i++)		//每有一个人代表进行一次游戏
	{
		for (int i = 0; i < m-1; i++)		//根据m的值来找出对应的结点之前的直接结点，并释放那个结点之后的结点方便操作
		{
			p = p->next;
		}
		looplist s = (looplist)malloc(sizeof(Lnode));
		s = p->next;
		m = p->next->password;		//记录密码并改变m值
		printf("%3d", p->next->number);		//输出编号
		p->next = p->next->next;
		free(s);		//释放对应结点
	}
}

void main()
{
	looplist L;
	int ini_m;		//初始化m的值
	int n;		//定义人数
        printf("请输入总人数：");
	scanf_s("%d", &n);
	printf("请输入初始密码：");
	scanf_s("%d", &m);
	if (n <= 0||m<=0) { printf("输入需为正"); return -1; }		//如果输入的人数/初始密码小于等于0则报错

	printf("请按顺序输入每个人的密码值(个数不超过总人数)：");
	Initlooplist(L, n);
	Josephring(L, ini_m, n);
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
