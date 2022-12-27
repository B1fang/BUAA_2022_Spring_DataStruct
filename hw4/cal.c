#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define MAXN 1000

int symbolPow(char sym){
	if(sym=='+'||sym=='-'){
		return 1;
	}
	else if(sym=='*'||sym=='/'){
		return 2;
	}
	return 3;
}

int main()
{
	char oriExp[MAXN]="";
	char backExp[MAXN]="";
	int ptr1=0;//与后缀式数组bE1配合使用
	char stack1[MAXN]="";
	int top1=-1;
	gets(oriExp);
	for(int i=0;i<strlen(oriExp);i++){
		if(oriExp[i]==' ')continue;
		if(isdigit(oriExp[i])){
			backExp[ptr1++]=oriExp[i];
		}
		else{
			if(oriExp[i]=='='){
				if(isdigit(backExp[ptr1-1]))backExp[ptr1++]='$';
				break;
			}
			if(isdigit(backExp[ptr1-1]))backExp[ptr1++]='$';
			if(top1==-1){//空栈入栈
				stack1[++top1]=oriExp[i];
				continue;
			}
			if(oriExp[i]==')'){
				while(stack1[top1]!='('){
					backExp[ptr1++]=stack1[top1];
					stack1[top1--]=0;
				}
				stack1[top1--]=0;
				continue;
			}
			if(symbolPow(oriExp[i])>symbolPow(stack1[top1])){
				stack1[++top1]=oriExp[i];
				continue;
			}
			else if(symbolPow(oriExp[i])<=symbolPow(stack1[top1])){
				while(stack1[top1]!='('&&top1!=-1&&symbolPow(oriExp[i])<=symbolPow(stack1[top1])){
					backExp[ptr1++]=stack1[top1];
					stack1[top1--]=0;
				}
				stack1[++top1]=oriExp[i];
				continue;
			}
		}
	}
	while(top1!=-1){
		backExp[ptr1++]=stack1[top1];
		stack1[top1--]=0;
	}
	backExp[ptr1]='\0';//至此后缀表达式构造完毕
	double stack2[MAXN]={0},tmp=0;
	int top2=-1;//与stack2配套使用
	double a,b;
	for(int i=0;i<strlen(backExp);i++){
		if(isdigit(backExp[i])){
			tmp=tmp*10+(double)(backExp[i]-'0');
		}
		if(backExp[i]=='$'){
			stack2[++top2]=tmp;
			tmp=0;
		}
		if(backExp[i]=='+'){
			b=stack2[top2--];
			a=stack2[top2--];
			stack2[++top2]=a+b;
		}
		else if(backExp[i]=='-'){
			b=stack2[top2--];
			a=stack2[top2--];
			stack2[++top2]=a-b;
		}
		else if(backExp[i]=='*'){
			b=stack2[top2--];
			a=stack2[top2--];
			stack2[++top2]=a*b;
		}
		else if(backExp[i]=='/'){
			b=stack2[top2--];
			a=stack2[top2--];
			stack2[++top2]=a/b;
		}
	}
	printf("%.2f",stack2[top2]);
	return 0;
}


