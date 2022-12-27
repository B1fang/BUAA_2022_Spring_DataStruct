#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<math.h>
#define MAX(x,y) (x>y)?x:y
#define MIN(x,y) (x<y)?x:y

typedef struct node{
	int num;
	struct node * next;
}lNode,*linkList;

int main()
{
	int n,m,q,cnt;
	scanf("%d%d%d",&n,&m,&q);
	linkList p,start,end,tmpp;
	
	for(int i=0;i<n;i++){
		p=(linkList)malloc(sizeof(lNode));
		if(i==0){
			start=p;
			end=p;
			p->num=i+1;
			p->next=NULL;
		}
		else{
			p->num=i+1;
			end->next=p;
			p->next=NULL;
			end=p;
		}
	}
	
	end->next=start;
	p=start;
	while(p->num!=q){
		tmpp=p;
		p=p->next;
	}
	cnt=1;
	while(n!=1){
		if(cnt==m){
			tmpp->next=p->next;
			free(p);
			p=tmpp;
			n--;
			cnt=0;
		}
		tmpp=p;
		p=p->next;
		cnt++;
	}
	printf("%d",p->num);
	free(p);
	return 0;
}


