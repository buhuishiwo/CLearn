#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXBIT 10000
#define MAXVALUE 100000
#define MAXLEAF 256
int n=0;
typedef struct{
    int weight;
    char ch;
    int parent,lch,rch;
}HuffmanTree;

typedef struct{        //Huffman编码结构体
    int bit[MAXBIT];   //该字符的哈夫曼编码
    int start;         //该编码在数组bit中的开始位置
    char ch_value;     //对应字符
}HCodeType;

void Delete(char text[],int i)
{
    for(int j=i;text[i]!='\0';n++)
    {
        text[j]=text[j+1];
    }
}
int Difch(char text[],char ch[])
{
    int num=0;
    int text_num=0;
    while(text[text_num]!='\0')
    {
        char *chr=strchr(ch,text[text_num]);
        if(ch[0]=='\0'||chr==NULL)
        {
            ch[text_num]=text[text_num];
            num++;
        }
        text_num++;
    }
    for(int i=0;i<text_num;i++)
    {
        printf("%c",ch[i]);
    }
    return num;
}
void Weight(char text[],int weight[])
{
    for(int i=0;i<n;i++)
    {
        int w=1;
        char now=text[i];
        for(int j=i+1;j<n;j++)
        {
            if(now==text[j])
            {
                w++;
                Delete(text, j);
            }
        }
        weight[i]=w;
    }
}
int TextStatistics(char text[], char ch[], int weight[]) {
    // 初始化索引
    int text_index = 0;         //字符串数组的索引
    int ch_index = 0;           //字符数组的索引
    int weight_index = 0;       //权重数组的索引
                
    // 遍历输入的字符串
    while(text[text_index]!='\0'){
        // 检查当前字符是否已经在ch数组中
        char* pos = strchr(ch,text[text_index]);
        // 如果ch数组为空，或者当前字符不在ch数组中
        if(ch[0]=='\0'  || pos == NULL ){
            // 将当前字符添加到ch数组中
            ch[ch_index] = text[text_index];
            // 并在weight数组中对应的位置增加1
            weight[ch_index] += 1;
            // 更新ch数组的索引
            ch_index++;
        }
        else{
            // 如果当前字符已经在ch数组中，找到它在weight数组中的位置
            weight_index = pos - ch ;
            // 并在weight数组中对应的位置增加1
            weight[weight_index] += 1;
        }
        // 更新text数组的索引，处理下一个字符
        text_index++;
    }
    // 在ch数组的末尾添加一个空字符，表示字符串的结束
    ch[ch_index] = '\0';
    // 返回ch数组中的字符数量
    return ch_index;
}

//暴力查找
void Select(HuffmanTree HT[],int range,int *s1,int *s2){
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
void CreateHuffmanTree(HuffmanTree HT[],int n,int weight[],char ch[])
{
    if(n<=1) return;
    int m=2*n-1;
    int s1,s2;
    for(int i=0;i<m;i++)
    {
        HT[i].parent=0;
        HT[i].lch=0;
        HT[i].rch=0;
    }
    for(int i=0;i<n;i++)
    {
//        scanf("%d",&HT[i].weight);
        HT[i].weight=weight[i];
        HT[i].ch=ch[i];
    }
    for(int i=n;i<m;++i)
    {
        Select(HT,i-1,&s1,&s2);
        HT[s1].parent=i;
        HT[s2].parent=i;
        HT[i].lch=s1;
        HT[i].rch=s2;
        HT[i].weight=HT[s1].weight+HT[s2].weight;
    }
}
void HuffmanCode(HuffmanTree HuffNodes[], HCodeType HuffCodes[], char ch[], int n) {
    //生成Huffman编码，Huffman编码存放在HuffCodes中（一个位置存储一个节点的哈夫曼编码，单个结点的哈夫曼编码在bit数组中)
    int start;
    for(int i =0 ;i<n;i++){
        start = n-2;  //字符ch[i]对应的Huffman编码（存储在bit数组中）起始位置，从右往左存.每个结点的哈夫曼编码的长度不超过（叶子结点个数n-1），因此bit数组只需要使用(n-1)的长度。
        //而哈夫曼编码是从哈夫曼树的叶子结点开始一直追溯到根结点按照左右赋予0/1值的，所以倒着编码，bit数组起始下标应该是(n-2)，每编码一位就减一
        HuffCodes[i].ch_value = ch[i];  // 存储该字符值
        for(int c = i , f=HuffNodes[i].parent ; f!=0; c =f,f=HuffNodes[f].parent){//从叶子到根逆向求编码
            --start;
            if(c == HuffNodes[f].lch)
            {
                HuffCodes[i].bit[start]=0;
            }
            else
            {
                HuffCodes[i].bit[start]=1;
            }
        }
        HuffCodes[i].start = start+1;
    }
}
//void HuffmanCode(HuffmanTree HuffNodes, HCodeType &HuffCodes, char ch[], int n)
//{
//    HuffCodes = (HCodeType)malloc((n+1)*sizeof(HTCode));
//    
//}
int main()
{
    int text_num;
    int weight[MAXVALUE];
    char text[MAXVALUE],ch[MAXVALUE];
    printf("请输如字符数量");
    scanf("%d",&n);
    getchar();
    printf("请输入字符串");
    for(int i=0;i<n;i++)
    {
        scanf("%c",&text[i]);
    }
    text_num=TextStatistics(text,ch,weight);
    HuffmanTree HT[100];
    HCodeType HCODE[MAXLEAF];
    CreateHuffmanTree(HT, text_num, weight, ch);
    for(int i=0;i<2*text_num-1;i++)
    {
        printf("%c ",HT[i].ch);
        printf("%d ",HT[i].weight);
        printf("%d ",HT[i].parent);
        printf("%d ",HT[i].lch);
        printf("%d ",HT[i].rch);
        printf("\n");
    }
    HuffmanCode(HT, HCODE, ch, text_num);

    for (int i=0; i<text_num; i++) {
        printf("%c的Huffman编码是：", ch[i]);

        for(int j=HCODE[i].start; j<n-1; j++)
            printf("%d", HCODE[i].bit[j]);

        printf("\n");
    }
    return 0;
}
