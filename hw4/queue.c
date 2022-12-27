#include<stdio.h>
#include<stdlib.h>
/*
	我的思路：
	用一个大循环去模拟每个周期（出队，入队）用一个变量去记录已经过的周期数；
	可以在出队的同时输出。
	现存版本的问题：
	应该如何合理地调整队列？思路没问题，但是应当避免使用浮点数
*/

typedef struct node{
	int number;
	int	timeOfArrive;
	struct node * next;
}qNode,*linkQueue;

int main(){
	int n,numOfPeople[100]={0};
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&numOfPeople[i]);
	}
	
	linkQueue front,rear,p;
	p=(linkQueue)malloc(sizeof(qNode));
	p->next=NULL;
	front=p;
	rear=p;
	int round=0,peopleCounter=0,numOfQueue=3;
	int ctPeople=0;
	while(front->next!=NULL||round<n){
		round++;
		if(round<=n){//顾客们入队
			for(int i=1;i<=numOfPeople[round];i++){
				p=(linkQueue)malloc(sizeof(qNode));
				p->number=(++peopleCounter);
				p->timeOfArrive=round;
				p->next=NULL;
				rear->next=p;
				rear=p;
				ctPeople++;
			}
		}
		if(ctPeople>=7*numOfQueue&&round<=n&&numOfQueue<5){
			numOfQueue++;
			if(ctPeople>=7*numOfQueue&&numOfQueue<5){
				numOfQueue++;
			}
		}
		for(int i=1;i<=numOfQueue&&(front->next!=NULL);i++){
			p=front->next;
			printf("%d : %d\n",p->number,round-p->timeOfArrive);
			front->next=p->next;
			free(p);
			ctPeople--;
		}
		if(front->next==NULL){//防止出现野指针
			rear=front;
		}
		if(ctPeople<7*numOfQueue&&numOfQueue>3){
			numOfQueue--;
			if(ctPeople<7*numOfQueue&&numOfQueue>3){
				numOfQueue--;
			}
		}
	}
	return 0;
}

