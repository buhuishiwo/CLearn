#include <stdio.h>
#include <string.h>
#define MAXLEN 255
typedef struct
{
    char ch[MAXLEN + 1];
    int length;
} SString;

void Enter(SString &s)
{
    char newchar[MAXLEN + 1];
    printf("输入字符串\n");
    scanf("%s", newchar);
    s.length = strlen(newchar);
    strcpy(s.ch, newchar);
}

void getNext(int *next, SString s)
{
    int n = s.length, j = 0,k=-1;            //next[0]=-1，其余右移
    next[0] = -1;
    while(j<n-1)             
    {
        if(k==-1||s.ch[j]==s.ch[k])
        {
            ++k;
            ++j;
            next[j]=k;
        }else{
            k=next[k];
        }
    }
    // int n = s.length,j=0;                //next[0]=0,正常next表
    // next[0] = 0;
    // for (int i = 1; i < n; i++) // next[0]=0，正常的 next 表
    // {
    //     while (j > 0 && s.ch[i] != s.ch[j])
    //     {
    //         j = next[j - 1];
    //     }
    //     if (s.ch[i] == s.ch[j])
    //     {
    //         j++;
    //     }
    //     next[i] = j;
    // }
}
void getNextval(int *next, SString s)
{
    int n = s.length, j = 0, k = -1;
    next[0] = -1;
    while (j < n - 1)
    {
        if (k == -1 || s.ch[j] == s.ch[k])
        {
            ++k;
            ++j;
            next[j] = (s.ch[j] != s.ch[k]) ? k : next[k];
        }
        else
        {
            k = next[k];
        }
    }
}
int indexKMF(SString s, SString t)
{
    int m = s.length, n = t.length, j = -1,i=0;                 //next[0]=-1，其余右移
    int next[n];
    getNext(next, t);
    while(i<m&&j<n){
        if(j==-1||s.ch[i]==t.ch[j]){
            ++i;
            ++j;
        }
        else
        {
            j=next[j];
        }
    }
    if(j==n)
    {
        return i-j;
    }
    // int m=s.length,n=t.length,j=0;               //next[0]=0,正常next表
    // getNext(next, t);
    // for(int i=0;i<m;i++)                         
    // {
    //     while(j>0&&s.ch[i]!=t.ch[j])
    //     {
    //         j=next[j-1];
    //     }
    //     if(s.ch[i]==t.ch[j])
    //     {
    //         j++;
    //     }
    //     if(j==n)
    //     {
    //         return (i-n+1);
    //     }
    // }
    
    return -1;
}

int main()
{
    SString s;
    SString t;
    Enter(s);
    Enter(t);
    printf("%s 在%s 中出现的第一个位置是%d\n", t.ch, s.ch, indexKMF(s, t) + 1);
}