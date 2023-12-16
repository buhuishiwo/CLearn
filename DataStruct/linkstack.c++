#include<stdio.h>
#include<stdlib.h>
 
typedef struct StackNode{
	char data;
	struct StackNode *next;
}*LinkStack;
 
void InitStack(LinkStack *S){
	*S = NULL;
}
 
void Pop(LinkStack *S, char *ch){
	*ch = (*S)->data;
	*S = (*S)->next;
}
 
void Push(LinkStack *S, char ch){
	LinkStack node = (LinkStack)malloc(sizeof(LinkStack));
	node->data = ch;
	node->next = *S;
	*S = node;
}
 
char GetTop(LinkStack S){
	return S->data;
}
 
bool In(char ch){
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || ch == '#'){
		return true;
	}else{
		return false;
	}
}
 
char Precede(char a, char b){					
	if (a == '+' || a == '-'){
		if (b == '+' || b == '-' || b == ')' || b == '#'){
			return '>';
		}else{
			return '<';
		}
	}else if (a == '*' || a == '/'){
		if (b == '+' || b == '-' || b == '*' || b == '/' || b == ')' || b == '#'){
			return '>';
		}else{
			return '<';
		}
	}else if (a == '('){
		if (b == ')'){
			return '=';
		}else if (b == '#'){					//表达式错误
			return '?';
		}else{
			return '<';
		}
	}else if (a == '#'){
		if (b == '#'){
			return '=';
		}else if (b == ')'){					//表达式错误
			return '?';
		}else {
			return '<';
		}
	}
}
 
char Operate(char a, char theta, char b){
	int A = a - 48;
	int B = b - 48;
	int C;
	if (theta == '+'){
		C = A + B ;
	}else if (theta == '-'){
		C = A - B ;
	}else if (theta == '*'){
		C = A * B ;
	}else if (theta == '/'){
		C = A / B ;
	}
	return C + '0';
}
 
void EvaluateExpression(){
	LinkStack OPTR,OPND;
	OPTR = (LinkStack)malloc(sizeof(LinkStack));			//存放运算符
	OPND = (LinkStack)malloc(sizeof(LinkStack));			//存放操作数
	InitStack(&OPTR);
	InitStack(&OPND);
	Push(&OPTR, '#');				
	char ch;
	scanf("%c", &ch);
	while(ch != '#' || GetTop(OPTR) != '#'){
		if (!In(ch)){
			Push(&OPND, ch);		//将数字压入 OPND 栈
			scanf("%c", &ch);
		}else{
			switch(Precede(GetTop(OPTR), ch)){
				case '<':
					Push(&OPTR,ch);
					scanf("%c", &ch);
					break;
				case '>':
					char theta,a,b;
					Pop(&OPTR,&theta);
					Pop(&OPND,&b);
					Pop(&OPND,&a);
					Push(&OPND,Operate(a,theta,b));
					break;
				case '=':
					char temp;
					Pop(&OPTR,&temp);
					scanf("%c", &ch);
					break;
				case '?':
					printf("表达式错误！");
					return;
			}
		}
	}
	printf("表达式的结果为：%c", GetTop(OPND));
}
 
int main()
{
	printf("请输入一个表达式(以#结束)：");
	EvaluateExpression();
}