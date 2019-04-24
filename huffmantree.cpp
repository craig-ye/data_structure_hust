// ConsoleApplication21.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;
/*定义霍夫曼树节点*/
typedef struct HTNode {
	int parent;/*记录双亲*/
	int Lchild;/*左右子树*/
	int Rchild;
	int Weight;/*记录权重*/
}HTNode;
typedef struct HTNode * HuffmanTree;
typedef char ** HuffmanCode;

/*在前k棵树种找到权重最小的树*/
int Min(HuffmanTree HT, int k) {
	int i = 0, min_weight = 0, min = 0;
	/*找出第一个双亲存在的节点，将其权值赋值给min_weight*/
	/*注意此处不能直接将HT[0].weight赋给min_weight，原因是如果HT[0].weight最小，那么在第一次构造二叉树时就会被选走，而后续的每一轮选择最小权值构造二叉树的比较
	还是先用HT[0].weight的值来进行判断，这样又会再次将其选走，从而产生逻辑上的错误。*/
	while (HT[i].parent != -1)
		i++;
	min_weight = HT[i].Weight;
	min = i;
	for (i; i < k; i++) {
		if (HT[i].Weight < min_weight&&HT[i].parent == -1) {
			min_weight = HT[i].Weight;
			min = i;
		}
	}
	/*找到最小权重的树，将其双亲置为1*/
	/*！！！！！注意这的HT的下标！！！！！一晚上才找出这个小问题，别写成HT[i]!!!!!!*/
	HT[min].parent = 1;
	return min;
}

/*从前k棵树中选出权重最小的两棵树,将其序号赋给min1和min2*/
Status SelectMin(HuffmanTree HT, int k, int &min1, int &min2) {
	min1 = Min(HT, k);
	min2 = Min(HT, k);
	return OK;
}


/*创建一课霍夫曼树，-1表示不存在*/
/*wet为一个记录权重的数组，类型为int*/
HuffmanTree CreateHuffmanTree(HuffmanTree HT, int *wet, int n) {
	int i = 0;
	int total = 2 * n - 1;/*有n个数据需要编码，即有n个叶子节点，也就有n-1个度为2的节点，总节点数为n+n-1=2*n-1*/
	/*初始状态下，前n个节点的双亲，左右子树应该均为-1，权重为对应的权重*/
	/*用HT的前n个分量存储n棵树(由n个待编码的数据组成)的森林*/
	/*申请total个int组成的动态数组*/
	HT = (HuffmanTree)malloc(total * sizeof(HTNode));
	if (!HT)
		return ERROR;
	for (i = 0; i < n; i++) {
		HT[i].Lchild = -1;
		HT[i].parent = -1;
		HT[i].Rchild = -1;
		HT[i].Weight = *wet;
		wet++;
	}

	/*对n到total的分量进行初始化*/
	for (i; i < total; i++) {
		HT[i].Lchild = -1;
		HT[i].Rchild = -1;
		HT[i].parent = -1;
		HT[i].Weight = 0;
	}
	/*用HT的后n-1个分量存储霍夫曼树*/
	/*调用函数SelectMin找出森林中两棵权重最小的树*/
	int min1 = 0, min2 = 0;
	for (i = n; i < total; i++) {
		SelectMin(HT, i, min1, min2);
		HT[min1].parent = i;
		HT[min2].parent = i;
		HT[i].Lchild = min1;
		HT[i].Rchild = min2;
		HT[i].Weight = HT[min1].Weight + HT[min2].Weight;
	}
	return HT;
}

/*从叶子节点开始逆向进行霍夫曼编码*/
/*HC用来储存霍夫曼编码值*/
Status HuffmanCoding(HuffmanTree HT, HuffmanCode &HC, int n) {
	/*HC本身是一个char类型数组的指针,其指向n个char类型的地址，所以给HC分配内存应该写成下面那样*/
	HC = (HuffmanCode)malloc(n * sizeof(char *));
	if (!HC)
		return ERROR;
	/*声明一个动态数组code，用来临时存储霍夫曼编码,数组含有n-1个霍夫曼码，加上一个'\0'终止符正好是n个元素，所以分配内存时*/
	char *code;
	code = (char *)malloc(n * sizeof(char));
	if (!code)
		return ERROR;
	code[n - 1] = '\0';/*让最后一个元素为终止符*/

	int i = 0;
	for (i = 0; i < n; i++) {
		int current = i;
		int father = HT[i].parent;
		int start = n - 1;
		while (father != -1) {
			if (current == HT[father].Lchild)
				code[--start] = '0';
			else
				code[--start] = '1';
			current = father;
			father = HT[father].parent;
		}
		/*HC[i]用于最终存储霍夫曼码，是char类型的数组，有n个char类型的数据*/
		HC[i] = (char *)malloc((n - start) * sizeof(char));
		if (!HC[i])
			return ERROR;
		/*从临时空间中复制到HC[i]中*/
		strcpy(HC[i], code + start);
	}
	/*释放临时存储空间*/
	free(code);
	code = NULL;
	return OK;
}

int main(void) {
	int amount = 0, i = 0;
	int *wet = (int *)malloc(amount * sizeof(int));
	printf("请输入要编码的字符个数(个数为整型且>1)");
	scanf("%d", &amount);
	while (amount <= 1) {
		printf("字符个数必须大于1\n");
		scanf("%d", &amount);
	}
	printf("请输入要编码的字符的权值");
	for (i = 0; i < amount; i++) {
		scanf("%d", wet + i);
	}
	HTNode H = { 0,0,0,0 };
	HuffmanTree HT =&H;
	HT = CreateHuffmanTree(HT, wet, amount);

	HuffmanCode HC;
	HuffmanCoding(HT, HC, amount);
	for (i = 0; i < amount; i++) 
	{
		puts(HC[i]);
	}
	free(wet);
	return OK;
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
