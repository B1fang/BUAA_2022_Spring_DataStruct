#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<math.h>
#define MAX(x,y) (x>y)?x:y
#define MIN(x,y) (x<y)?x:y

typedef struct node{
	char c;
	struct node * next;
}lNode,*linkList;

char input[20000];

int main()
{
	int hush[95]={0},tmp;
	char table[95]="",tmps[32]="";
	gets(tmps);
	int i,j;
	for(i=0,j=0;i<strlen(tmps);i++){
		tmp=(int)(tmps[i]-' ');
		if(hush[tmp]==0){
			table[j++]=tmps[i];
			hush[tmp]++;
		}
	}
	for(i=0;i<95;i++){
		if(hush[i]==0){
			table[j++]=(char)(i+' ');
			hush[i]++;
		}
	}
	//构建环形链表///////////////////////////////////
	i=0;
	linkList p,start,end;
	p=(linkList)malloc(sizeof(lNode));
	p->c=table[i++];
	start=p;
	end=p;
	p->next=NULL;
	while(i<95){
		p=(linkList)malloc(sizeof(lNode));
		p->c=table[i++];
		end->next=p;
		p->next=NULL;
		end=p;
	}
	end->next=start;
	//获得密钥///////////////////////////////////////
	int tmp1,n=95,step;//tmp1用于存储ASCII码值,n记录节点个数,step用于存储移动次数 
	char headAlpha=start->c;
	char in,out,key[95]="";
	linkList tmpp=end;//此指针指向p的前序节点 
	p=start;
	while(n>1){
		in=p->c;
		tmp1=(int)in;
		
		tmpp->next=p->next;
		free(p);
		p=tmpp->next;
		n--;
		
		step=(tmp1-1)%n;
		while(step){
			tmpp=p;
			p=p->next;
			step--;
		}
		out=p->c;
		key[in-' ']=out;
	}
	in=p->c;
	free(p);
	out=headAlpha;
	key[in-' ']=out;
	//文件加密//////////////////
	FILE * fp1,*fp2;
	fp1=fopen("in.txt","r");
	fp2=fopen("in_crpyt.txt","w");
	//fread(input,sizeof(char),20000,fp1);
	//for(i=0;i<strlen(input);i++){
	//	if(input[i]<=126&&input[i]>=32){
	//		input[i]=key[input[i]-' '];
	//	}
	//}
	//fwrite(input,sizeof(char),strlen(input),fp2);
	while(fgets(input,20000,fp1)!=NULL){
		for(int i=0;i<strlen(input);i++){
			if(input[i]<=126&&input[i]>=32){
				input[i]=key[input[i]-' '];
			}
		}
		fputs(input,fp2);
	}
	fclose(fp1);
	fclose(fp2);
	return 0;
}



