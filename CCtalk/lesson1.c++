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
void PLength(SString s)
{
	printf("字符串长度为：%d\n",s.length);
} 
int index(SString s, SString s2) {					//查找指定字符串首次出现位置
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

void DeleteCh(SString &s, char ch)						//删除指定字符
{
	    int i, count;
		 count = 0;
	    
	    for (i = 0; i <= s.length; i++) {
	        if (s.ch[i] == ch) {
	            count++;
	        } else {
	            s.ch[i - count] = s.ch[i];
	        }
	    }
	    
	    s.length -= count;
	printf("删除成功后结果%s",s.ch);
}
void concat(SString &s1, SString &s2) {						//两个串相连
    int i, j;
    for (i = s1.length, j = 0; j < s2.length; i++, j++) {
        s1.ch[i] = s2.ch[j];
    }
    s1.length += s2.length;
}
void Print(SString s)
{
	printf("字符串输出%s\n",s.ch);
}
int main()
{
	SString s,s2;
	Enter(s);
	// DeleteCh(s2,'n');
	Enter(s2);
	// PLength(s);
	Print(s2);
	concat(s,s2);
	Print(s);
	printf("查找字符串首次出现在：%d位置\n",index(s,s2)); 
}