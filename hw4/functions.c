#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
	char funcName[25];
}stack;

typedef struct child
{
	char funcName[25];
	struct child * nextChild;
}childNode,*childLink;

typedef struct head
{
	char funcName[25];
	struct head * nextHead;
	childLink nextChild;
	int cnt;//记录调用函数的数目
}headNode,*headLink;

headLink findHead(headLink head,char target[]){
	headLink ph=head;
	while(ph!=NULL){
		if(strcmp(ph->funcName,target)==0){
			return ph;
		}
		ph=ph->nextHead;
	}
	return NULL;
}

childLink findChild(childLink childHead,char target[]){
	childLink pc=childHead;
	while(pc!=NULL){
		if(strcmp(pc->funcName,target)==0){
			return pc;
		}
		pc=pc->nextChild;
	}
	return NULL;
}

int main(){
    stack stk[200];
	int top=-1,cnt=0;
	int op;
	headLink head,rear;//二维链表头尾节点
	headLink ph,ph1;//用于遍历头节点的指针变量
    headLink tmph;//暂时存储新建的头节点
	childLink pc,pc1;//用于遍历孩子节点的指针变量
	childLink tmpc;//暂时存储新建的孩子节点
    while(top!=-1||cnt==0){
        scanf("%d",&op);
        if(op==0){
            top--;
        }
        else if(op==8){
            scanf("%s",stk[++top].funcName);
            if(cnt==0){
                ph=(headLink)malloc(sizeof(headNode));
                ph->nextChild=NULL;
                ph->nextHead=NULL;
                ph->cnt=0;
                strcpy(ph->funcName,stk[top].funcName);
                head=ph;
                rear=ph;
            }
            else{
                ph=findHead(head,stk[top].funcName);
                if(ph==NULL){
                    ph=(headLink)malloc(sizeof(headNode));
                    ph->cnt=0;
                    ph->nextChild=NULL;
                    ph->nextHead=NULL;
                    strcpy(ph->funcName,stk[top].funcName);
                    rear->nextHead=ph;
                    rear=ph;
                }
                ph=findHead(head,stk[top-1].funcName);
                if(ph->cnt==0){
                    pc=(childLink)malloc(sizeof(childNode));
                    pc->nextChild=NULL;
                    strcpy(pc->funcName,stk[top].funcName);
                    ph->nextChild=pc;
                    ph->cnt++;
                }
                else{
                    tmpc=ph->nextChild;
                    pc=findChild(tmpc,stk[top].funcName);
                    if(pc==NULL){
                        pc=tmpc;
                        while(pc!=NULL){
                            tmpc=pc;
                            pc=pc->nextChild;
                        }
                        pc=(childLink)malloc(sizeof(childNode));
                        pc->nextChild=NULL;
                        strcpy(pc->funcName,stk[top].funcName);
                        tmpc->nextChild=pc;
                        ph->cnt++;
                    }
                }
            }
        }
        cnt++;
    }
    ph=head;
	while(ph!=NULL){
		if(ph->cnt){
			printf("%s:",ph->funcName);
			pc=ph->nextChild;
			printf("%s",pc->funcName);
			pc=pc->nextChild;
			while(pc!=NULL){
				printf(",%s",pc->funcName);
				pc=pc->nextChild;
			}
			printf("\n");
		}
		ph=ph->nextHead;
	}
    return 0;
}

