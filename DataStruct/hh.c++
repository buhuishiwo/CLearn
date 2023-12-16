#include<stdio.h>
#include<stdlib.h>
typedef struct LNode
{
	int data;
	struct LNode *next; 
}LNode,*LinkList;

void Initsert(LinkList L,int i,int x)
{
	LinkList p=L->next;
	int j=0;
	LinkList s;
	s=new LNode;
	s->data=x;
	s->next=NULL;
	while(p&&j!=i)
	{
		j++;
		p=p->next;
	}
	s->next=p->next;
	p->next=s;
	
}

LinkList createlist()
{
		LinkList L=(LinkList)malloc(sizeof(LNode));
		L->next=NULL;
		LinkList p=(LinkList)malloc(sizeof(LNode));
		p->data=-1;
		L->next=p;
		for(int i=0;i<5;i++)
		{
			LinkList p=(LinkList)malloc(sizeof(LNode));
			p->data=i;
			p->next=L->next;
			L->next=p;
		}
		p->next=NULL;
		return L;
}
void sprintlist(LinkList L)
{
	LinkList p=L->next;
	while(p){
		printf("%d\n",p->data);
		p=p->next;
	}
}

void LNodedelete(LinkList L,int i)
{
	LinkList p=L;
	LinkList q;
	int j=0;
	while(p&&j<i-1)
	{
		j++;
		p=p->next;
	}
	q=p->next;
	p->next=p->next->next;
	delete q;
}
int main()
{
	LinkList L=createlist();
	Initsert(L,2,10);
	LNodedelete(L,2);
	sprintlist(L);
}