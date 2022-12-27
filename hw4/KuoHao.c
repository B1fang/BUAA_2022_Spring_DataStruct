/*
1.�����ĳ�������Ϊ'{'ʱ������ǰ����δƥ�������Ϊ'('ʱ�������'('�����ż������кţ� 

2.������һ����ƥ���������')'��'}'ʱ������������ż������кţ�

3.�����������ʱ�������ڲ�ƥ���������ʱ������������ż������кš�
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXN 205 

typedef struct {
    char ch;
    int rowRecord;
}stackNode;

int top=-1;
int isEmpty(){
    if(top==-1)return 1;
    return 0;
}
int isFull(){
    if(top==MAXN-1)return 1;
    return 0;
}
void stackPush(stackNode stack[],char ch,int rowCnt){
    if(isFull())return;
    stack[++top].ch=ch;
    stack[top].rowRecord=rowCnt;
}
void stackPop(stackNode stack[]){
    if(isEmpty())return;
    stack[top].ch=0;
    stack[top--].rowRecord=0;
}

int main(){
    FILE * fp;
    fp=fopen("example.c","r");
    stackNode stack[MAXN];
    char kH[MAXN]="";
    char row[MAXN]="";
    int ptr1=0;
    int flag1=0;//���ڱ�ʶ����ע��ʶ��״̬
    int rowCnt=0;
    while(fgets(row,MAXN,fp)!=NULL){//ȡ�����е�����
        if(row[0]=='\n')continue;
		rowCnt++;
        for(int i=0;i<strlen(row);i++){
            if(row[i]=='/'&&row[i+1]=='/'&&flag1==0){//��Ⲣ��������ע��
                break;
            }
            if(flag1){//��Ⲣ��������ע��1
                for(;i<strlen(row);i++){
                    if(row[i]=='*'&&row[i+1]=='/'){
                        flag1=0;
                        break;
                    }
                }
            }
            if(row[i]=='/'&&row[i+1]=='*'){//��Ⲣ��������ע��2
                flag1=1;
                for(;i<strlen(row);i++){
                    if(row[i]=='*'&&row[i+1]=='/'){
                        flag1=0;
                        break;
                    }
                }
            }
            if(row[i]=='\"'){//��Ⲣ�����ַ�������
				for(i++;i<strlen(row);i++){
                    if(row[i]=='\"'){
						break;
                    }
                }
            }
            if(row[i]=='\''){//��Ⲣ�����ַ�����
				for(i++;i<strlen(row);i++){
                    if(row[i]=='\''){
						break;
                    }
                }
            }
            if(flag1==0){
               if(row[i]=='{'||row[i]=='('||row[i]==')'||row[i]=='}'){
                   kH[ptr1++]=row[i];
               }
               if(stack[top].ch=='('&&row[i]=='{'){
               		printf("without maching '%c' at line %d",stack[top].ch,stack[top].rowRecord);
               		fclose(fp);
                    return 0;
			   }
			   if(row[i]=='{'||row[i]=='('){
                   stackPush(stack,row[i],rowCnt);
               }
			   else if(row[i]==')'||row[i]=='}'){
                   if(stack[top].ch=='('&&row[i]==')'){
                       stackPop(stack);
                   }
                   else if(stack[top].ch=='{'&&row[i]=='}'){
                       stackPop(stack);
                   }
                   else{
                        if(rowCnt==79){
                            rowCnt++;
                        }
                        printf("without maching '%c' at line %d",row[i],rowCnt);
                        fclose(fp);
                        return 0;
                   }
               }
            }
        }
    }
    if(top!=-1){
        printf("without maching '%c' at line %d",stack[top].ch,stack[top].rowRecord);
        fclose(fp);
        return 0;
    }
    for(int i=0;i<ptr1;i++){
        printf("%c",kH[i]);
    }
    fclose(fp);
    return 0;
}


