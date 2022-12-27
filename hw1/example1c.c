#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<math.h>
#define MAX(x,y) (x>y)?x:y
#define MIN(x,y) (x<y)?x:y

void spaceDel(char exp[]);
int symCheck(char p[]);
int calclt(char p[]); 

int main()//v1.1默认开头项符号为正 
{
	int i;
	char exp[500]="";
	char*p[500];int cnt2=0;//记录项数，分隔各项 
	int symbol[500]={0},cnt1=0;//记录加、减号数目及排列顺序 
	gets(exp);
	spaceDel(exp);
	for(i=0;exp[i]!='=';i++){
		if(exp[i]=='+')symbol[cnt1++]=1;
		else if(exp[i]=='-')symbol[cnt1++]=-1;
	}
	
	p[cnt2++]=&exp[0];
	for(i=1;exp[i]!='=';i++){
		if(exp[i]=='+'||exp[i]=='-'){
			exp[i]='\0';
			p[cnt2++]=&exp[i+1];
		}
	}
	exp[i]='\0';//至此分隔过程已结束 
	
	int sum=calclt(p[0]);
	for(int j=1;j<cnt2;j++){
		sum+=symbol[j-1]*calclt(p[j]);
	}
	printf("%d",sum);
	return 0;
}

void spaceDel(char exp[]){
	int i,j;
	for(i=j=0;exp[i]!='\0';i++){
		if(exp[i]!=' '){
			exp[j++]=exp[i];
		}
	}
	exp[j]='\0';
}

int symCheck(char p[]){//用于判断是连乘or连除or不做运算 
	for(int i=0;i<strlen(p);i++){
		if(p[i]=='*')return 1;
		else if(p[i]=='/')return -1;
	}
	return 0;
}

int calclt(char p[]){//此函数用于处理连乘&连除 
	int sum;
	int sym[500]={0},cnt2=0;
	char*p1[500];
	int cnt1=0,tmp=strlen(p),cal=symCheck(p);
	if(cal!=0){
		p1[cnt1++]=&p[0];
		for(int i=0;i<tmp;i++){
			if(p[i]=='*'||p[i]=='/'){
				if(p[i]=='*'){
					sym[cnt2++]=1; 
				}
				else if(p[i]=='/'){
					sym[cnt2++]=-1;
				}
				p[i]='\0',p1[cnt1++]=&p[i+1];
			}
		}
		sum=atoi(p1[0]);
		for(int i=1;i<cnt1;i++){
			if(sym[i-1]==1){
				sum*=atoi(p1[i]);
			}
			else if(sym[i-1]==-1){
				sum/=atoi(p1[i]);
			}
		}
	}
	//if(cal==1){
	//	p1[cnt1++]=&p[0];
	//	for(int i=0;i<tmp;i++){
	//		if(p[i]=='*'){
	//			p[i]='\0',p1[cnt1++]=&p[i+1];
	//		}
	//	}
	//	for(int i=0;i<cnt1;i++){
	//		sum*=atoi(p1[i]);
	//	}
	//}
	//else if(cal==-1){
	//	p1[cnt1++]=&p[0];
	//	for(int i=0;i<tmp;i++){
	//		if(p[i]=='/'){
	//			p[i]='\0';
	//			p1[cnt1++]=&p[i+1];
	//		}
	//	}
	//	sum=atoi(p1[0]);
	//	for(int i=1;i<cnt1;i++){
	//		sum/=atoi(p1[i]);
	//	}
	//}
	else if(cal==0){
		sum=atoi(p);
	}
	return sum;
}



