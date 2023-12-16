#include<stdio.h>
#include<stdlib.h>
#define ERROR -2

#define MAXSIZE 100
#define OVERFLOW -1
typedef struct{
	int *base;
	int front;
	int rear;
}Squeue;

void Init(Squeue &Q)
{
	Q.base = (int*)malloc(MAXSIZE);
	if(!Q.base) exit(OVERFLOW);
	Q.front=Q.rear=0;
}

int QueueLenght(Squeue Q)
{
	return (Q.rear-Q.front+MAXSIZE)%MAXSIZE;
}

void EnQueue(Squeue &Q,int e)
{
	if((Q.rear+1)%MAXSIZE==Q.front) exit(ERROR);
	Q.base[Q.rear]=e;
	Q.rear=(Q.rear+1)%MAXSIZE;
}

void DeQueue(Squeue &Q,int &e)
{
	if(Q.front==Q.rear) exit(ERROR);
	e=Q.base[Q.front];
	Q.front=(Q.front+1)%MAXSIZE;
}

int GetQueue(Squeue Q)
{
	if(Q.front!=Q.rear)
	{
		return Q.base[Q.front];
	}
}

int main()
{
	int e;
	Squeue L;
	Init(L);
	for(int i=1;i<=10;i++)
	{
		EnQueue(L,i);
	}
	for(int i=0;i<=9;i++)
	{
		DeQueue(L,e);
		printf("%d ",e);
	}
	printf("%d ",QueueLenght(L));
	return 0;
}