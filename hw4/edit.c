#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node{
	int op;
	int pos;
	char str[100];
	struct node * next;
}lNode,*linkList;

int main()
{	
	int ptr;//字符串删除、添加使用的下标变量
	linkList p,top;
	p=(linkList)malloc(sizeof(lNode));
	top=p;top->next=NULL;
	char str[600]="",tmp[600]="";//tmp用来存储这个，啊，字符串处理过程中的，中间量
	gets(str);
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		p=(linkList)malloc(sizeof(lNode));
		scanf("%d%d ",&p->op,&p->pos);
		gets(p->str);
		p->next=top->next;
		top->next=p;
	}
	char buffer[10];
	gets(buffer);
	int op1;
	while(1){
		scanf("%d",&op1);
		if(op1==3){
			p=top->next;
			if(p==NULL)continue;//无前序操作，忽略此次询问
			if(p->op==1){
				//在相关位置删除给定字符串即可
				ptr=0;
				for(int i=0;i<p->pos;i++){
					tmp[ptr++]=str[i];
				}
				for(int i=p->pos+strlen(p->str);i<strlen(str);i++){
					tmp[ptr++]=str[i];
				}
				tmp[ptr]='\0';
				strcpy(str,tmp);
				memset(tmp,'\0',sizeof(tmp));
			}
			else if(p->op==2){
				//在相关位置添加
				ptr=0;
				for(int i=0;i<p->pos;i++){
					tmp[ptr++]=str[i];
				}
				for(int i=0;i<strlen(p->str);i++){
					tmp[ptr++]=p->str[i];
				}
				for(int i=p->pos;i<strlen(str);i++){
					tmp[ptr++]=str[i];
				}
				tmp[ptr]='\0';
				strcpy(str,tmp);
				memset(tmp,'\0',sizeof(tmp));
			}
			//栈顶操作出栈
			top->next=p->next;
			free(p);
		}
		if(op1==1){
			//入栈并进行添加操作
			p=(linkList)malloc(sizeof(lNode));
			p->op=op1;
			p->next=top->next;
			top->next=p;
			scanf("%d ",&p->pos);//入栈完成,待进行字符串的添加
			gets(p->str);
			ptr=0;
			for(int i=0;i<p->pos;i++){
				tmp[ptr++]=str[i];
			}
			for(int i=0;i<strlen(p->str);i++){
				tmp[ptr++]=p->str[i];
			}
			for(int i=p->pos;i<strlen(str);i++){
				tmp[ptr++]=str[i];
			}
			tmp[ptr]='\0';
			strcpy(str,tmp);
			memset(tmp,'\0',sizeof(tmp));
		}
		if(op1==2){
			//入栈并进行删减操作，注意保存删除的字符串方便回溯
			int lengthOfDelete;
			p=(linkList)malloc(sizeof(lNode));
			p->next=top->next;
			top->next=p;
			p->op=op1;
			scanf("%d %d",&p->pos,&lengthOfDelete);//入栈完成，得到删除长度，未获得删除内容串，待进行字符串的删除
			ptr=0;
			if((p->pos+lengthOfDelete-1)>strlen(str)){
				lengthOfDelete=strlen(str)+1-p->pos;
			}
			for(int i=0;i<p->pos;i++){
				tmp[ptr++]=str[i];
			}
			int ptr1=0;
			for(int i=p->pos;i<p->pos+lengthOfDelete;i++){//向栈顶存储删除的字符串
				p->str[ptr1++]=str[i];
			}
			p->str[ptr1]='\0';
			for(int i=p->pos+lengthOfDelete;i<strlen(str);i++){
				tmp[ptr++]=str[i];
			}
			tmp[ptr]='\0';
			strcpy(str,tmp);
			memset(tmp,'\0',sizeof(tmp));
		}
		if(op1==-1){
			break;
		}
	}
	puts(str);
	return 0;
}


