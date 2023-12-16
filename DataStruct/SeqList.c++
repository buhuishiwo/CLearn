#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#define MAXSIZE 100
typedef struct stu					//定义结构体
{
	char sno[20];
	char sname[20];
	int grade;
}STUDENT;

typedef struct{						//定义数组结构体
	STUDENT  stu[MAXSIZE];
	int length;
}SqList;

void shuru(SqList  &L)						//创建顺序表
{
	int n;
	printf("请输入数据量大小\n");
	scanf("%d",&n);
	L.length=n;
	for(int i=0;i<L.length;i++)
	{
		printf("学号：");
		scanf("%s",L.stu[i].sno);
		printf("姓名：");
		scanf("%s",L.stu[i].sname);
		printf("成绩：");
		scanf("%d",&L.stu[i].grade);
	}

}

void print(SqList  L)									//打印顺序表
{
	printf("打印数据如下\n");
	for(int i=0;i<L.length;i++)
	{
		printf("%s  %s   %d\n",L.stu[i].sno,L.stu[i].sname,L.stu[i].grade);
	}
}


void chazhao(SqList  L,STUDENT x)				//查找
{
	int u =0;
	for(int i=0;i<L.length;i++)
	{
		if(strcmp(L.stu[i].sname,x.sname)==0)
			{printf("查找数据为：学号 %s，姓名 %s，成绩 % d\n",L.stu[i].sno,L.stu[i].sname,L.stu[i].grade);
			u=1;}
	}
	if(u==0)
	{
		printf("查无此人\n");
	}
}

void insert(SqList  &L,int i,STUDENT x)					//插入
{
	if(L.length>=MAXSIZE || i>L.length)
	{
		printf("超出界限\n");
		exit(1);
	}
	for(int j=L.length-1;j>=i;j--)
	{
		L.stu[j+1]=L.stu[j];										//后移顺序表
	}
	L.stu[i]=x;
	L.length++;
}

void unionList(SqList  &L1,SqList  &L2)					//合并顺序表
{
	for(int i=0;i<L2.length;i++)
	{
		STUDENT b=L2.stu[i];
		if(strcmp(L1.stu[i].sname,L2.stu[i].sname)!=0)
			insert(L1,L1.length,b);
	}

}

int main()
{
	SqList L;
	STUDENT x;
	SqList N;
	shuru(N);
	print(N);
	strcpy(x.sname,"li");
	strcpy(x.sno,"04");
	x.grade=100;
	chazhao(N,x);
	shuru(L);
	print(L);
	unionList(L, N);
	insert(L,100,x);
	print(L);
	return 0;


}