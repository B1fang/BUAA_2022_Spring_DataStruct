#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#define MAXN 1000

typedef struct node{
    struct node * lChild;
    struct node * rChild;
    int flag;//0存数字，1存符号
    int num;
    char ch;
}tNode , *tPtr;

int symbolPow(char sym){
	if(sym=='+'||sym=='-'){
		return 1;
	}
	else if(sym=='*'||sym=='/'){
		return 2;
	}
	return 3;
}

int cal(tPtr root){
    if(root->flag==0)return root->num;
    int numA,numB;
    char sym=root->ch;
    numA=cal(root->lChild);
    numB=cal(root->rChild);
    if(sym=='+')return (numA+numB);
    else if(sym=='-')return (numA-numB);
    else if(sym=='*')return (numA*numB);
    else if(sym=='/')return (numA/numB);
}

int main(){
    char oriExp[MAXN]="";
    gets(oriExp);
    char backExp[MAXN]="";
    int ptr1=0;//与后缀式数组bE1配合使用
    char stack1[MAXN]="";
	int top1=-1;//符号栈栈顶
    for(int i=0;i<strlen(oriExp);i++){//构造一个数字由'$'结尾的后缀式串
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
    tPtr stack2[1000],p;
    int top2=-1;
    int sum=0;
    for(int i=0;i<strlen(backExp);i++){
        if(backExp[i]=='$'){
            stack2[++top2]=(tPtr)malloc(sizeof(tNode));
            stack2[top2]->flag=0;
            stack2[top2]->num=sum;sum=0;
            stack2[top2]->lChild=NULL;
            stack2[top2]->rChild=NULL;
        }
        else if(isdigit(backExp[i])){
            sum=sum*10+(int)(backExp[i]-'0');
        }
        else{
            p=(tPtr)malloc(sizeof(tNode));
            p->ch=backExp[i];
            p->flag=1;
            p->rChild=stack2[top2];
            p->lChild=stack2[top2-1];
            stack2[top2--]=NULL;
            stack2[top2--]=NULL;
            stack2[++top2]=p;
        }
    }
    tPtr root=stack2[top2];
    printf("%c",root->ch);
    if(root->lChild->flag==0){
        printf(" ");
		printf("%d",root->lChild->num);
    }
    else{
        printf(" ");
		printf("%c",root->lChild->ch);
    }
    if(root->rChild->flag==0){
        printf(" ");
		printf("%d",root->rChild->num);
    }
    else{
        printf(" ");
		printf("%c",root->rChild->ch);
    }
    printf("\n");
    printf("%d",cal(root));
    return 0;
}

