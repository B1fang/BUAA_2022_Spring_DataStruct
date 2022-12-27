#include <stdio.h>

int top=-1;

int isEmpty(int top){
    if(top==-1)return 1;
    return 0;
}

int isFull(int top){
    if(top==99)return 1;
    return 0;
}

void stackPush(int stack[],int num){
    if(isFull(top)){
        printf("error ");
        return;
    }
    stack[++top]=num;
}

void stackPop(int stack[]){
    if(isEmpty(top)){
        printf("error ");
        return;
    }
    printf("%d ",stack[top--]);
}

int main(){
    int stack[105]={0};
    int op,num;
    while(1){
        scanf("%d",&op);
        if(op==-1)break;
        if(op){
            scanf("%d",&num);
            stackPush(stack,num);
        }
        else if(!op){
            stackPop(stack);
        }
    }
    return 0;
}


