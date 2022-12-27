#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<math.h>
#define MAX(x,y) (x>y)?x:y
#define MIN(x,y) (x<y)?x:y

typedef struct node{
	char word[100];
	int cnt;
	struct node * next;
}lNode,*linkList;

int main()
{
	int cnt=0,flg1=1;
	FILE * fp;
	fp=fopen("article.txt","r");
	char proWord[100]="";
	linkList p,start,end;
	p=(linkList)malloc(sizeof(lNode));
	start=p;
	end=p;
	p->cnt=-1;
	p->next=NULL;
	
	while(flg1){
		int k=0,flg2=0;
		char c;
		memset(proWord,0,sizeof(proWord));
		//for(int i=0;i<strlen(originWord);i++){
		//	if(isalpha(originWord[i])){
		//		proWord[k++]=tolower(originWord[i]);
		//	}
		//}
		//proWord[k]='\0';
		while(1){
			if((c=fgetc(fp))==EOF){
				proWord[k]='\0';
				flg1=0;
				break;
			}
			if(isalpha(c)==0&&flg2==1){
				proWord[k]='\0';
				break;
			}
			else if(isalpha(c)){
				proWord[k++]=tolower(c);
				flg2=1;
			}
		}
		if(end->cnt==-1){
			end->cnt=1;
			strcpy(end->word,proWord);
			cnt++;
		}
		else{
			p=start;
			while(p!=NULL){
				if(strcmp(p->word,proWord)==0){
					(p->cnt)++;
					goto flag1;
				}
				p=p->next;
			}
			p=(linkList)malloc(sizeof(lNode));
			end->next=p;
			p->next=NULL;
			end=p;
			end->cnt=1;
			strcpy(end->word,proWord);
			cnt++;
		}
		flag1:;
	}
	
	int tmp;
	char tmps[100]="";
	for(int i=0;i<cnt;i++){
		p=start;
		while(p->next!=NULL){
			if(strcmp(p->word,p->next->word)>0){
				tmp=p->cnt;
				p->cnt=p->next->cnt;
				p->next->cnt=tmp;
				strcpy(tmps,p->word);
				strcpy(p->word,p->next->word);
				strcpy(p->next->word,tmps);
			}
			p=p->next;
		}
	}
	p=start;
	while(p!=NULL){
		if(strlen(p->word)!=0){
			printf("%s %d",p->word,p->cnt);
			printf("\n");
		}
		p=p->next;
	}
	linkList tmpp;
	p=start;
	while(p!=NULL){
		tmpp=p;
		p=p->next;
		free(tmpp);
	}
	fclose(fp);
	return 0;
}


