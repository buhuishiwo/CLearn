#include<stdio.h>
#include<string.h>
#define MAXLEN 255

typedef struct{
    char ch[MAXLEN+1];
    int length;
}SString;

void Enter(SString &s)
{
    char newchar[MAXLEN+1];
    printf("输入字符串\n");
    scanf("%s",newchar);
    s.length=strlen(newchar);
    strcpy(s.ch,newchar);
}
int indexBF(SString s, SString s2) {                    //查找指定字符串首次出现位置
    int i=1,j=1;
    while(i<=s.length && j<=s2.length)
    {
        if(s.ch[i-1]==s2.ch[j-1])
        {
            ++i;
            ++j;
        }
        else
        {
            i=i-j+2;
            j=1;
        }
    }
    if(j>s2.length)
    {
        return i-s2.length;
    }
    else
    {
        return -1;
    }
}

void getnext(SString t, int next[])
{
    int i=1,j=0;
    next[1]=0;
    while(i<t.length)
    {
        if(j==0||t.ch[i]==t.ch[j])
        {
            ++i;
            ++j;
            next[i]=j;
        }
        else
        {
            j=next[j];
        }
    }
}

int indexKMP(SString s,SString t,int pos)
{
    int i=pos,j=1;
    while (i<=s.length && i<=t.length) {
        if(j==0||s.ch[i]==t.ch[j])
        {
            ++i;
            ++j;
        }
        else
        {
            j=next[j];
        }
    }
}

void Print(SString s)
{
    printf("字符串输出%s\n",s.ch);
}
int main()
{
    SString s,s2;
    
    Enter(s);
    Enter(s2);
    Print(s2);
    Print(s);
    printf("查找字符串首次出现在：%d位置\n",indexBF(s,s2));
}
