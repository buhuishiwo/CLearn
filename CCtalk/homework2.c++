#include<stdio.h>
#include<stdlib.h>
#define ERROR -1

typedef struct QNode{
	int data;
	struct QNode *next;
}Qnode,*QueuePtr;

typedef struct{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

void Init(LinkQueue &Q)
{
	Q.front=Q.rear=(QueuePtr)malloc(sizeof(Qnode));
	Q.front->next=NULL;
}

void EnQueue(LinkQueue &Q,int e)
{
	QueuePtr p = (QueuePtr)malloc(sizeof(Qnode));
	p->data = e;
	p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
}

void DeQueue(LinkQueue &Q,int &e)
{
	if(Q.front==Q.rear) exit(ERROR);
	QueuePtr p;
	p=Q.front->next;
	e=p->data;
	Q.front->next=p->next;
	if(Q.rear==p) Q.rear=Q.front;
	free(p);
}

void Delete(LinkQueue &Q,int n)
{
	
}

int GetHead(LinkQueue Q)
{
	if(Q.front!=Q.rear)
	{
		return Q.front->next->data;
	}
}

void PrintQueue(LinkQueue Q)
{
	QueuePtr p;
	p=Q.front->next;
	while(p)
	{
		printf("%d\n",p->data);
		p=p->next;
	}
	
	
}

int main()
{
	int e;
	LinkQueue L;
	Init(L);
	for(int i=1;i<=10;i++)
	{
		EnQueue(L,i);
	}
	PrintQueue(L);
	DeQueue(L,e);
	printf("%d\n",e);
	printf("%d",GetHead(L));
	return 0;
}