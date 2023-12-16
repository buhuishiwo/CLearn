#include<stdio.h>
#include<stdlib.h>

// 定义链表节点结构
typedef struct Node {
    int tel;
    struct Node *next;
} Lnode,*LinkList;

void PrintList(LinkList L)
{
 LinkList p = L;
 while (p)
 {
  p = p->next;
  printf("%d\n", p->tel);
 }
}

void InitList(LinkList L, int x)
{
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

void UnioList(LinkList l1,LinkList l2)
{
	LinkList p1,p2,prev;
	p1=l1;
	p2=l2;
	while(p1&&p2)
	{
		if(p1->tel<=p2->tel)
		{
			prev=p1;
			p1=p1->next;
		}
		else if(p1->tel>p2->tel)
		{
			if (prev != NULL) prev->next = p2;
            prev = p2;
            p2 = p2->next;
            prev->next = p1;

		}
	}
	if (p1 == NULL) prev->next = p2;
}

int main()
{
	LinkList l1 = (LinkList)malloc(sizeof(Lnode));
	LinkList l2 = (LinkList)malloc(sizeof(Lnode));
	l1->next=NULL;
	InitList(l1,3);
	InitList(l2,3);
	UnioList(l1,l2);
	PrintList(l2);
	return 0;
}