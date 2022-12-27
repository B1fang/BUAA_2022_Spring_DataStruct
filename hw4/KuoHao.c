/*
1.当检测的程序括号为'{'时，若其前序尚未匹配的括号为'('时，输出该'('左括号及所在行号； 

2.当遇到一个不匹配的右括号')'或'}'时，输出该右括号及所在行号；

3.当程序处理完毕时，还存在不匹配的左括号时，输出该左括号及所在行号。
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
    int flag1=0;//用于标识多行注释识别状态
    int rowCnt=0;
    while(fgets(row,MAXN,fp)!=NULL){//取得所有的括号
        if(row[0]=='\n')continue;
		rowCnt++;
        for(int i=0;i<strlen(row);i++){
            if(row[i]=='/'&&row[i+1]=='/'&&flag1==0){//检测并跳过单行注释
                break;
            }
            if(flag1){//检测并跳过多行注释1
                for(;i<strlen(row);i++){
                    if(row[i]=='*'&&row[i+1]=='/'){
                        flag1=0;
                        break;
                    }
                }
            }
            if(row[i]=='/'&&row[i+1]=='*'){//检测并跳过多行注释2
                flag1=1;
                for(;i<strlen(row);i++){
                    if(row[i]=='*'&&row[i+1]=='/'){
                        flag1=0;
                        break;
                    }
                }
            }
            if(row[i]=='\"'){//检测并跳过字符串常量
				for(i++;i<strlen(row);i++){
                    if(row[i]=='\"'){
						break;
                    }
                }
            }
            if(row[i]=='\''){//检测并跳过字符常量
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


