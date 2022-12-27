//文件压缩-Huffman实现
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 32

struct tnode {			//Huffman树结构
	char c;		
	int weight;		//树节点权重，叶节点为字符和它的出现次数
	struct tnode *left,*right;
} ; 
int Ccount[128]={0};		//存放每个字符的出现次数，如Ccount[i]表示ASCII值为i的字符出现次数 
struct tnode *Root=NULL; 	//Huffman树的根节点
char HCode[128][MAXSIZE]={{0}}; //字符的Huffman编码，如HCode['a']为字符a的Huffman编码（字符串形式） 
int Step=0;			//实验步骤 
FILE *Src, *Obj;
	
void statCount();		//步骤1：统计文件中字符频率
void createHTree();		//步骤2：创建一个Huffman树，根节点为Root 
void makeHCode();		//步骤3：根据Huffman树生成Huffman编码
void atoHZIP(); 		//步骤4：根据Huffman编码将指定ASCII码文本文件转换成Huffman码文件

void print1();			//输出步骤1的结果
void print2(struct tnode *p);	//输出步骤2的结果 
void print3();			//输出步骤3的结果
void print4();			//输出步骤4的结果

int main()
{
        if((Src=fopen("input.txt","r"))==NULL) {
	        fprintf(stderr, "%s open failed!\n", "input.txt");
		return 1; 
	}
	if((Obj=fopen("output.txt","w"))==NULL) {
		fprintf(stderr, "%s open failed!\n", "output.txt");
		return 1;
	}
	scanf("%d",&Step);		//输入当前实验步骤 
	
	statCount();			//实验步骤1：统计文件中字符出现次数（频率）
	(Step==1)?print1():1;   	//输出实验步骤1结果	
	createHTree();			//实验步骤2：依据字符频率生成相应的Huffman树
	(Step==2)?print2(Root):2; 	//输出实验步骤2结果	
	makeHCode();		//实验步骤3：依据Root为树的根的Huffman树生成相应Huffman编码
	(Step==3)?print3():3;   	//输出实验步骤3结果
	(Step>=4)?atoHZIP(),print4():4;//实验步骤4：据Huffman编码生成压缩文件，并输出实验步骤4结果	

	fclose(Src);
	fclose(Obj);
        return 0;
} 

//【实验步骤1】开始 
void statCount()
{
        char row[1005]="";
	while(fgets(row,1000,Src)!=NULL){
		for(int i=0;i<strlen(row);i++){
			if(row[i]=='\n')continue;
			Ccount[(int)row[i]]++;
		}
	}
	Ccount[0]=1;
}



//【实验步骤1】结束

//【实验步骤2】开始
typedef struct node{
	struct tnode * tPtr;
	struct node * next;
}lNode,*linkList;
void createHTree()
{
	linkList start=NULL,end=NULL,p1=NULL;
	struct tnode * p2=NULL;
	struct tnode * tmpp=NULL;
	start=(linkList)malloc(sizeof(lNode));
	end=start;
	start->next=NULL;
	start->tPtr=NULL;
	int numCounter=0;
	for(int i=0;i<128;i++){//初始化
		if(Ccount[i]==0)continue;
		numCounter++;
		p1=(linkList)malloc(sizeof(lNode));
		p1->next=NULL;
		p1->tPtr=NULL;
		end->next=p1;
		end=p1;
		p2=(struct tnode *)malloc(sizeof(struct tnode));
		p2->left=NULL,p2->right=NULL;
		p2->c=i;
		p2->weight=Ccount[i];
		p1->tPtr=p2;
	}
	for(int i=0;i<=numCounter;i++){//冒泡
		p1=start->next;
		while(p1->next!=NULL){
			if(p1->tPtr->weight>p1->next->tPtr->weight){
				tmpp=p1->tPtr;
				p1->tPtr=p1->next->tPtr;
				p1->next->tPtr=tmpp;
			}
			p1=p1->next;
		}
	}
	while(start->next->next!=NULL){
		p2=(struct tnode *)malloc(sizeof(struct tnode));
		p2->weight=start->next->tPtr->weight+start->next->next->tPtr->weight;
		p2->left=start->next->tPtr;
		p2->right=start->next->next->tPtr;
		p1=start->next;
		start->next=start->next->next;
		free(p1);
		p1=start->next;
		start->next=start->next->next;
		free(p1);
		if(start->next==NULL) {
			p1=(linkList)malloc(sizeof(lNode));
			p1->next=NULL;
			start->next=p1;
			p1->tPtr=p2;
		}
		else{
			linkList p3;
			p1=start->next;
			while(p1!=NULL&&!(p2->weight<p1->tPtr->weight)){
				p3=p1;
				p1=p1->next;
			}
			p1=(linkList)malloc(sizeof(lNode));
			p1->next=p3->next;
			p3->next=p1;
			p1->tPtr=p2;
		}
	}
	Root=start->next->tPtr;
}


//【实验步骤2】结束

//【实验步骤3】开始
char code[MAXSIZE];

void traverse(struct tnode *p,int ptr){
	if(p==NULL)return;
	if(p->left==NULL){//是个树叶结点
		code[ptr]='\0';
		strcpy(HCode[(int)p->c],code);
		return;
	}
	code[ptr]='0';
	traverse(p->left,ptr+1);
	code[ptr]='1';
	traverse(p->right,ptr+1);
}

void makeHCode()
{
	traverse(Root,0);
} 



//【实验步骤3】结束

//【实验步骤4】开始
char s[10005]="";
char hc;

void atoHZIP()
{
	FILE * src=fopen("input.txt","r");
	FILE * obj=fopen("output.txt","w");
	while((hc=getc(src))!=EOF){
		if(hc=='\n')continue;
		strcat(s,HCode[(int)hc]);
	}
	strcat(s,HCode[0]);
	int sum;
	unsigned char ch;
	int i,flag=0;
	for(i=0;i<strlen(s);i+=8){
		sum=0;
		if(i+7>=strlen(s)){
			flag=1;
			break;
		}
		for(int j=i;j<i+8;j++){
			sum=2*sum+(int)(s[j]-'0');
		}
		ch=(unsigned char)sum;
		fputc(ch,obj);
		printf("%x",ch);
	}
	if(flag){
		for(;i<strlen(s);i++){
			sum=2*sum+(int)(s[i]-'0');
		}
		ch=(unsigned char)sum;
		fputc(ch,obj);
		printf("%x",ch);
	}
	fclose(src);
	fclose(obj);
}


//【实验步骤4】结束

void print1()
{
	int i;
	printf("NUL:1\n");
	for(i=1; i<128; i++)
		if(Ccount[i] > 0)
			printf("%c:%d\n", i, Ccount[i]);
}

void print2(struct tnode *p)
{
	if(p != NULL){
		if((p->left==NULL)&&(p->right==NULL)) 
			switch(p->c){
				case 0: printf("NUL ");break;
				case ' ':  printf("SP ");break;
				case '\t': printf("TAB ");break;
				case '\n':  printf("CR ");break;
				default: printf("%c ",p->c); break;
			}
		print2(p->left);
		print2(p->right);
	}
}

void print3()
{
	int i;
	
	for(i=0; i<128; i++){
		if(HCode[i][0] != 0){
			switch(i){
				case 0: printf("NUL:");break;
				case ' ':  printf("SP:");break;
				case '\t': printf("TAB:");break;
				case '\n':  printf("CR:");break;
				default: printf("%c:",i); break;
			}
			printf("%s\n",HCode[i]);
		}
	}
} 

void print4()
{
	long int in_size, out_size;
	
	fseek(Src,0,SEEK_END);
	fseek(Obj,0,SEEK_END);
	in_size = ftell(Src);
	out_size = ftell(Obj);
	
	printf("\n原文件大小：%ldB\n",in_size);
	printf("压缩后文件大小：%ldB\n",out_size);
	printf("压缩率：%.2f%%\n",(float)(in_size-out_size)*100/in_size);
}

