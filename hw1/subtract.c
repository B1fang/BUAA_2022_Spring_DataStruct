#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<math.h>
#define MAX(x,y) (x>y)?x:y
#define MIN(x,y) (x<y)?x:y

void funcMinus(char num1[],char num2[]);
int cmp(char num1[],char num2[]);

int main()
{
	char numA[100]="",numB[100]="";
	gets(numA);gets(numB);
	char *num1, *num2,*num3;
	for(int i=0;i<strlen(numA);i++){
		if(numA[i]!='0'){
			num1=&numA[i];
			break;
		}
	}
	for(int i=0;i<strlen(numB);i++){
		if(numB[i]!='0'){
			num2=&numB[i];
			break;
		}
	}
	if(strlen(num1)>strlen(num2)){
		funcMinus(num1,num2);
		for(int i=0;i<strlen(num1);i++){
			if(num1[i]!='0'){
				num3=&num1[i];
				break;
			}
		}
		puts(num3);
	}
	else if(strlen(num1)<strlen(num2)){
		funcMinus(num2,num1);
		printf("-");
		for(int i=0;i<strlen(num2);i++){
			if(num2[i]!='0'){
				num3=&num2[i];
				break;
			}
		}
		puts(num3);
	}
	else if(strlen(num1)==strlen(num2)){
		if(cmp(num1,num2)==1){
			funcMinus(num1,num2);
			for(int i=0;i<strlen(num1);i++){
				if(num1[i]!='0'){
					num3=&num1[i];
					break;
				}
			}
			puts(num3);
		}
		else if(cmp(num1,num2)==-1){
			funcMinus(num2,num1);
			printf("-");
			for(int i=0;i<strlen(num2);i++){
				if(num2[i]!='0'){
					num3=&num2[i];
					break;
				}
			}
			puts(num3);
		}
		else{
			printf("0");
		}
	}
	return 0;
}

void funcMinus(char num1[],char num2[]){
	int i=strlen(num1)-1,j=strlen(num2)-1;
	while(j>=0){
		num1[i]=num1[i]-num2[j]+'0';
		i--,j--;
	}
	for(int k=strlen(num1)-1;k>=0;k--){
		if(num1[k]<'0'){
			num1[k]+=10;
			num1[k-1]-=1;
		}
	} 
}
int cmp(char num1[],char num2[]){
	for(int i=0;i<strlen(num1);i++){
		if(num1[i]>num2[i])return 1;
		else if(num1[i]<num2[i])return -1;
	}
	return 0;
}

