#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<math.h>
#define MAX(x,y) (x>y)?x:y
#define MIN(x,y) (x<y)?x:y

typedef struct node{
	char bookName[100];
	char authorName[100];
	char pressName[100];
	int date;
	struct node * link;
}lNode,*linkList;

void sortList(linkList start){//冒泡排序 
	linkList p1=start,p2=start,p3=NULL;
	char tmps[100]={0};
	int tmp;
	while(p1!=NULL){
		p2=start;
		while(p2!=NULL){
			p3=p2->link;
			if(p3==NULL){
				break;
			}
			if(strcmp(p2->bookName,p3->bookName)>0){
				strcpy(tmps,p2->authorName);strcpy(p2->authorName,p3->authorName);strcpy(p3->authorName,tmps);
				strcpy(tmps,p2->bookName);strcpy(p2->bookName,p3->bookName);strcpy(p3->bookName,tmps);
				strcpy(tmps,p2->pressName);strcpy(p2->pressName,p3->pressName);strcpy(p3->pressName,tmps);
				tmp=p2->date;p2->date=p3->date;p3->date=tmp;
			}
			p2=p2->link;
		}
		p1=p1->link;
	}
} 

int main()
{
	FILE *fp1=fopen("books.txt","r");
	FILE *fp2=fopen("ordered.txt","w");
	linkList start,end,p;
//初始化链表////////////////////////////////////////////////////////////////////////////	
	int cnt=0;
	do{
		p=(linkList)malloc(sizeof(lNode));
		if(cnt==0){
			start=p;
			end=p;
			p->link=NULL;
		}
		else{
			end->link=p;
			p->link=NULL;
			end=p;
		}
		cnt++;
	}while(fscanf(fp1,"%s%s%s%d",p->bookName,p->authorName,p->pressName,&p->date)!=EOF);
	p=start;
	for(int i=1;i<cnt;i++){
		if(i==cnt-1){
			end=p;
			p->link=NULL;
		}
		p=p->link;
	}
	sortList(start);
//具体功能实现////////////////////////////////////////////////////////////////////////////////////////////////	
	int op;
	char str[100];
	while(1){
		scanf("%d",&op);
		if(op==0){
			break;
		}
		else if(op==1){		//添加项目 
			p=(linkList)malloc(sizeof(lNode));
			end->link=p;
			end=p;
			p->link=NULL;
			fscanf(stdin,"%s%s%s%d",p->bookName,p->authorName,p->pressName,&p->date);
			sortList(start);
		}
		else if(op==2){		//检索向shell输出 
			scanf("%s",str);
			p=start;
			while(p!=NULL){
				for(int i=0;i<strlen(p->bookName)-strlen(str)+1;i++){//
					for(int j=0;j<strlen(str);j++){
						if(p->bookName[i+j]!=str[j]){
							goto flag1;
						}
					}
					printf("%-50s%-20s%-30s%-10d\n",p->bookName,p->authorName,p->pressName,p->date);
					break;
					flag1:;
				}
				p=p->link;
			}
		}
		else if(op==3){		//删除项目 
			scanf("%s",str);
			p=start;
			linkList p2;
			int tru;
			while(p!=NULL){
				tru=0;
				for(int i=0;i<strlen(p->bookName)-strlen(str)+1;i++){//
					for(int j=0;j<strlen(str);j++){
						if(p->bookName[i+j]!=str[j]){
							goto flag2;
						}
					}
					if(p==start){
						start=p->link;
						free(p);
						p=start;
					}
					else{
						p2=start;
						while(p2->link!=p){
							p2=p2->link;
						}
						p2->link=p->link;
						free(p);
						p=p2->link;
					}
					tru=1;
					break;
					flag2:;
				}
				if(tru==0){
					p=p->link;
				}
			}
		}
	}
	
	//向文件输出图书信息////////////////////////////////////////////////////////////////////////////////////////////
	p=start;
	while(p!=NULL){
		if(strlen(p->bookName)!=0)fprintf(fp2,"%-50s%-20s%-30s%-10d\n",p->bookName,p->authorName,p->pressName,p->date);
		p=p->link;
	} 
	
	//销毁链表///////////////////////////////////////////////////////////////////////////////////////////////////////
	p=start;
	while(p!=NULL){
		start=p->link;
		free(p);
		p=start;
	} 
	//关闭文件/////////////////////////////////////////////////////////////////////////////////////////////////////////
	fclose(fp1);
	fclose(fp2);
	return 0;
}


