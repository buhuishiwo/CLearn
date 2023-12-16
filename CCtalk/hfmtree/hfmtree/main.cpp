#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
    int weight;
    char ch;
    int parent,lch,rch;
}HTNode,*HuffmanTree;

typedef char **HuffmanCode;

void sum(int a[])           //计算字符串中非重复字符个数
{
    char s[1000];
    printf("请输入待转码的字符串:");
    scanf("%s",s);
    int i;
    for(i=0;i<=26;i++)a[i]=0;
    int j=0;
    while(s[j]!='\0')
    {
        a[s[j]-96]++;           //a~z 字符的 ASCII 码值减去 96 就是对应的索引
        j++;
    }
}

//暴力查找
void Select(HuffmanTree HT,int range,int *s1,int *s2){
    //先找第一个最小值 。

    int min1=1000;        //给定一个足够大的值
    for(int index1=0;index1<=range;index1++){
        
        if(HT[index1].weight < min1 && HT[index1].parent ==0){
            //判断该结点是否被选过。如果该结点parent为0，则其为没有选过的叶结点。否则，说明其被选过
                min1 = HT[index1].weight;
                *s1 = index1 ;
        }
    }
    
    //找第2个最小值
    int min2 = 1000;
    for(int index2=0;index2<=range ;index2++){
        if(HT[index2].weight < min2 && HT[index2].parent ==0 && index2!=*s1){
            //判断该结点是否被选过。还要判断其是否被s1选了
                min2 = HT[index2].weight;
                *s2 = index2 ;
        }
    }
    
}
void CreateHuffmanTree(HuffmanTree &HT,int a[])             //构建哈夫曼树
{
    int n=26;
    if(n<=1) return;
    int m=2*n-1;
    int s1,s2;
    HT = (HuffmanTree)malloc((m)*sizeof(HTNode));
    for(int i=1;i<=m;i++)
    {
        HT[i].parent=0;
        HT[i].lch=0;
        HT[i].rch=0;
    }
    for(int i=1;i<=n;i++)
    {
        HT[i].weight=a[i];
        HT[i].ch=(char)(i+96);
    }
    for(int i=n;i<=m;++i)
    {
        Select(HT,i-1,&s1,&s2);
        HT[s1].parent=i;
        HT[s2].parent=i;
        HT[i].lch=s1;
        HT[i].rch=s2;
        HT[i].weight=HT[s1].weight+HT[s2].weight;
    }
}

void CreateHuffmanCode(HuffmanTree HT,HuffmanCode&HC)           //构建哈夫曼编码
{
    char *cd;
    int n=26;
    int f,start,c;
    cd=new char[n];
    cd[n-1]='\0';
    HC=new char*[n+1];
    for(int i=1;i<=n;i++)
    {
        start=n-1;
        c=i;
        f=HT[i].parent;
        while(f!=0)
        {
            --start;
            if(HT[f].lch==c) cd[start]='0';
            else cd[start]='1';
            c=f;
            f=HT[f].parent;
        }
        HC[i]=new char[n-start];
        for(int j=0;j<n-start;j++)
        {
            HC[i][j]=cd[start+j];
        }
    }
    delete cd;
}
void Decode(HuffmanTree HT)             //译码函数
{
    char str_ent[100];
    int f,i;
    int n=26;
    printf("请输入二进制编码");
    getchar();
    scanf("%s",str_ent);
    f=2*n-1;
    i=0;
    printf("解码后的字符串是：");
    while(str_ent[i]!='\0')
    {
        if(str_ent[i]=='0')
        {
            f=HT[f].lch;
        }
        else
        {
            f=HT[f].rch;
        }
        if(f<=n)
        {
            printf("%c",HT[f].ch);
            f=2*n-1;
        }
        i++;
    }
    printf("\n");
}


int main()
{
    HuffmanTree H;
    HuffmanCode HC;
    int n=26;
    int a[27];
    sum(a);
    CreateHuffmanTree(H, a);
    CreateHuffmanCode(H,HC);
    for(int i=1;i<=n;i++)
    {
        if(H[i].weight!=0)
        {
            printf("%c的哈夫曼编码是%s\n",H[i].ch,HC[i]);
        }
    }
    
    Decode(H);
    return 0;
}
