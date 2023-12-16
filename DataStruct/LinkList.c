#include <stdio.h>
#include<stdlib.h>
typedef struct Lnode {
	int tel;
	struct Lnode *next;
}Lnode,*LinkList;

void InitList(LinkList L, int x)
{
	printf("初始化链表\n");
	LinkList p = L;
	for (int i = 0; i < x; i++)
	{
		LinkList p = (LinkList)malloc(sizeof(Lnode));
		printf("enter data\n");
		scanf("%d", &p->tel);
		p->next = L->next;
		L->next = p;
	}
}

void PrintList(LinkList L)
{
	LinkList p = L->next;
	while (p!=NULL)
	{
		printf("%d\n", p->tel);
		p = p->next;
	}
}

void Insert(LinkList L, int x,int n)
{
	printf("插入新节点999\n");
	LinkList p = L;
	LinkList s;
	s= (LinkList)malloc(sizeof(Lnode));
	s->tel = n;
	int i = 0;
	while (p&&i != x)
	{
		i++;
		p=p->next;
	}
	s->next = p->next;
	p->next = s;
}

void Delete(LinkList L, int x)
{
	printf("删除第二个节点\n");
	LinkList p = L;
	LinkList n;
	int i = 0;
	while (p&&i <x-1)
	{
		i++;
		p = p->next;
	}
	n = p->next;
	p->next = p->next->next;
	free(n);
}

int main()
{
	LinkList L = (LinkList)malloc(sizeof(Lnode));
	L->next = NULL;
	InitList(L, 3);
	Insert(L, 2, 999);
	Delete(L, 2);
	PrintList(L);
	return 0;
}