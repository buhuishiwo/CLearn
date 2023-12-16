#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXBIT 10000
#define MAXVALUE 100000
#define MAXLEAF 256

typedef struct{
    int weight;
    int parent,lch,rch;
}HTNode,*HuffmanTree;

typedef struct{        //Huffman编码结构体
    int bit[MAXBIT];   //该字符的哈夫曼编码
    int start;         //该编码在数组bit中的开始位置
    char ch_value;     //对应字符
} HCodeType;

void input(char str[]){
    printf("请输入字符串\n");
    
    scanf("%c",str);
}

//暴力查找
void Select(HuffmanTree HT,int range,int *s1,int *s2){
    //先找第一个最小值 。

    int min1=1000;        //给定一个足够大的值
    for(int index1=1;index1<=range;index1++){
        
        if(HT[index1].weight < min1 && HT[index1].parent ==0){
            //判断该结点是否被选过。如果该结点parent为0，则其为没有选过的叶结点。否则，说明其被选过
                min1 = HT[index1].weight;
                *s1 = index1 ;
        }
    }
    
    //找第2个最小值
    int min2 = 1000;
    for(int index2=1;index2<=range ;index2++){
        if(HT[index2].weight < min2 && HT[index2].parent ==0 && index2!=*s1){
            //判断该结点是否被选过。还要判断其是否被s1选了
                min2 = HT[index2].weight;
                *s2 = index2 ;
        }
    }
    
}

//不暴力
void Select2(HuffmanTree HT, int end, int *s1, int *s2)
{
    int min1, min2;
    //遍历数组初始下标为 1
    int i = 1;
    //找到还没构建树的结点
    while(HT[i].parent != 0 && i <= end){
        i++;
    }
    min1 = HT[i].weight;
    *s1 = i;
   
    i++;
    while(HT[i].parent != 0 && i <= end){
        i++;
    }
    //对找到的两个结点比较大小，min2为大的，min1为小的
    if(HT[i].weight < min1){
        min2 = min1;
        *s2 = *s1;
        min1 = HT[i].weight;
        *s1 = i;
    }else{
        min2 = HT[i].weight;
        *s2 = i;
    }
    //两个结点和后续的所有未构建成树的结点做比较
    for(int j=i+1; j <= end; j++)
    {
        //如果有父结点，直接跳过，进行下一个
        if(HT[j].parent != 0){
            continue;
        }
        //如果比最小的还小，将min2=min1，min1赋值新的结点的下标
        if(HT[j].weight < min1){
            min2 = min1;
            min1 = HT[j].weight;
            *s2 = *s1;
            *s1 = j;
        }
        //如果介于两者之间，min2赋值为新的结点的位置下标
        else if(HT[j].weight >= min1 && HT[j].weight < min2){
            min2 = HT[j].weight;
            *s2 = j;
        }
    }
}
void CreateHuffmanTree(HuffmanTree &HT,int n)
{
    if(n<=1) return;
    int m=2*n-1;
    int s1,s2;
    HT = (HuffmanTree)malloc((m+1)*sizeof(HTNode));
    for(int i=1;i<=m;i++)
    {
        HT[i].parent=0;
        HT[i].lch=0;
        HT[i].rch=0;
    }
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&HT[i].weight);
    }
    for(int i=n+1;i<=m;++i)
    {
        Select(HT,i-1,&s1,&s2);
        HT[s1].parent=i;
        HT[s2].parent=i;
        HT[i].lch=s1;
        HT[i].rch=s2;
        HT[i].weight=HT[s1].weight+HT[s2].weight;
    }
}

int TextStatistics(char text[], char ch[], int weight[], int *length) {
    //统计每种字符的出现频次，返回出现的不同字符的个数ch_index
    //出现的字符存放在ch中，对应字符的出现频次存放在weight中, ch_index为ch中字符种类数
    //length为text长度

    int text_index = 0;   //text字符串索引
    int ch_index = 0;     //计字符数组增加索引，仅用于出现不同字符时，将该字符加入到ch[]中。仅自增
    int weight_index = 0; //频数更新索引。用于指定weight[]要更新频数的位置
                
    while(text[text_index]!='\0'){
        //查找ch中，是否存在字符text[text_index]，返回查到的第一个字符的位置
        char* pos = strchr(ch,text[text_index]);
        
        //如果ch中无该字符。或者ch为空。就将text[text_index]加入到ch中
        if(ch[0]=='\0'  || pos == NULL ){
    
            //加入到统计字符数组中
            ch[ch_index] = text[text_index];
                                      
            //新增一个字符的频数，当所有字符都统计完之后再计算频率
            weight[ch_index] += 1;
            ch_index++;
            
        }
        
        //如果字符串中有该字符
        else{
            //找到该字符的索引位置，更新其频数
            weight_index = pos - ch ;
            weight[weight_index] += 1;

        }
        
        text_index++;
    }
    ch[ch_index] = '\0';//添加结束符

    //根据频数计算频率
    int index=0;
    while(weight[index]!=0){
    weight[index]/=text_index;
    index++;
    }

    *length = text_index;  // 此时text_index即为源字符串text长度
    return ch_index; //最终 ch_index的值即为text字符串中不同字符的个数
}

void HuffmanCode(HuffmanTree HuffNodes, HCodeType HuffCodes[], char ch[], int n) {
    //生成Huffman编码，Huffman编码存放在HuffCodes中（一个位置存储一个节点的哈夫曼编码，单个结点的哈夫曼编码在bit数组中)
    int start;
    for(int i =0 ;i<n;i++){
        start = n-2;  //字符ch[i]对应的Huffman编码（存储在bit数组中）起始位置，从右往左存.每个结点的哈夫曼编码的长度不超过（叶子结点个数n-1），因此bit数组只需要使用(n-1)的长度。
        //而哈夫曼编码是从哈夫曼树的叶子结点开始一直追溯到根结点按照左右赋予0/1值的，所以倒着编码，bit数组起始下标应该是(n-2)，每编码一位就减一
        HuffCodes[i].ch_value = ch[i];  // 存储该字符值
        for(int c = i , f=HuffNodes[i].parent ; f!=-1; c =f,f=HuffNodes[f].parent){//从叶子到根逆向求编码
            if(c == HuffNodes[f].lch) HuffCodes[i].bit[start--]=0;
            else HuffCodes[i].bit[start--]=1;
        }
        HuffCodes[i].start = start+1;
    }
}

int main()
{
    HuffmanTree HT;
    HuffmanTree HT2;
    HCodeType HCODE[MAXLEAF];
    char str[MAXVALUE],ch[MAXLEAF];
    int result,length,n;
    int weight[MAXLEAF];
    input(str);
    
    n = TextStatistics(str, ch, weight, &length);
    
    CreateHuffmanTree(HT,8);
    HuffmanCode(HT2, HCODE, ch, n);
    for(int i=0;i<n;i++)
    {
        printf("%c的哈夫曼编码是：",ch[i]);
        
        for(int j=HCODE[i].start;j<n-1;j++)
        {
            printf("%d",HCODE[i].bit[j]);
        }
        printf("\n");
    }
    for(int i=1;i<=2*8-1;i++)
    {
        printf("%d ",HT[i].weight);
        printf("%d ",HT[i].parent);
        printf("%d ",HT[i].lch);
        printf("%d ",HT[i].rch);
        printf("\n");
    }
}
