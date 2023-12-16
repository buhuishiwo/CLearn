#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct
{
    char val;
    int weight;
    int parent,lchild,rchild;
}HTNode,*HuffmanTree;

typedef char **HuffmanCode;

void Select(HuffmanTree &HT,int n,int &s1,int &s2)
{
    
    int min1=1000,min2=1000;//需要给初始值一个足够大的值，可以使得每次进入函数时都可以重新比较
    for(int i=1;i<=n;i++)
    {
        if(HT[i].weight<min1&&HT[i].parent==0)
        {
            min1=HT[i].weight;
            s1=i;
        }
    }//打擂法寻找第一个最小数的序号
    
    for(int i=1;i<=n;i++)
    {
        if(i==s1)
        {
            continue;
        }
        if(HT[i].weight<min2&&HT[i].parent==0)
        {
            min2=HT[i].weight;
            s2=i;
        }
        
    }//打擂法寻找第二个最小数的序号
}

// 定义一个函数，用于删除数组中的元素
void DeleteArr(char *val,int j)
{
    // 从给定的位置开始，将后面的元素向前移动一位
    for(int i=j;val[i]!='\0';i++)
    {
        val[i]=val[i+1];
    }
}

// 定义一个函数，用于计算字符的权重（出现次数）
void weightval(int *weightarr,char *val,int size)
{
    // 从第二个元素开始遍历数组
    for(int i=1;val[i]!='\0';i++)
    {
        // 记录当前字符
        char aim=val[i];
        // 初始化权重为1
        int weight=1;
        // 从当前字符的下一个元素开始遍历数组
        for(int j=i+1;val[j]!='\0';j++)
        {
            // 如果找到相同的字符
            if(aim==val[j])
            {
                // 权重加1
                weight++;
                // 删除这个字符
                DeleteArr(val,j);
            }
        }
        // 记录这个字符的权重
        weightarr[i]=weight;
    }
}

void CreateHuffmanTree(HuffmanTree &HT,int n,int *weightarr,char *val)
{
    int s1=0,s2=1;
    if(n<=1) return;
    int m=2*n-1;
    HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));
    
    for(int i=1;i<=m;i++)
    {
        HT[i].parent=0;
        HT[i].lchild=0;
        HT[i].rchild=0;
    }
    
    for(int i=1;val[i]!='\0';i++)
    {
        HT[i].val=val[i];
        HT[i].weight=weightarr[i];
    }

    for(int i=n+1;i<=m;i++)
    {
        Select(HT,i-1,s1,s2);
        HT[s1].parent=i;
        HT[s2].parent=i;
        HT[i].lchild=s1;
        HT[i].rchild=s2;
        HT[i].weight=HT[s1].weight+HT[s2].weight;
    }
    
    for(int i=1;i<=m;i++)
    {
        printf("%c ",HT[i].val);
        printf("%d ",HT[i].weight);
        printf("%d ",HT[i].parent);
        printf("%d ",HT[i].lchild);
        printf("%d\n",HT[i].rchild);
    }
}

void CreatHuffmanCode(HuffmanTree &HT,HuffmanCode &HC,int n)
{
    int start;
    int c;
    int f;
    HC = (char**)malloc((n+1) * sizeof(char*));
    char* cd = (char*)malloc(n * sizeof(char));
    cd[n-1]='\0';
    for(int i=1;i<=n;i++)
    {
        start=n-1;
        c=i;
        f=HT[i].parent;
        while(f!=0)
        {
            start--;
            if(HT[f].lchild==c)
            {
                cd[start]='0';
            }
            else
            {
                cd[start]='1';
            }
            c=f;
            f=HT[f].parent;
        }
        HC[i] = (char*)malloc((n-start) * sizeof(char));
        strcpy(HC[i],&cd[start]);
    }
    free(cd);
    for (int i = 1; i <=n; i++)
    {
        printf("Huffman code for character %c: %s\n", HT[i].val, HC[i]);
    }
}


int main()
{
    
    int size;
    int n;
    HuffmanTree HT;
    HuffmanCode HC;
    printf("请输入字符串长度：\n");
    scanf("%d",&size);
    getchar();
    char val[size+1];
    int weightarr[size+1];
    printf("请输入字符串：\n");
    for(int i=1;i<=size;i++)
    {
        scanf("%c",&val[i]);
    }
    weightval(weightarr,val,size);
    for(int i=0;val[i]!='\0';i++)
    {
        n=i;
    }
    CreateHuffmanTree(HT,n,weightarr,val);
    CreatHuffmanCode(HT,HC,n);
    return 0;
}
