#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<math.h>
#define MAX(x,y) (x>y)?x:y
#define MIN(x,y) (x<y)?x:y

int numCounter1(char num[]);
int numCounter2(char num[]);

int main()
{
	char num[105]="";
	int cnt1,cnt2=0,cnt3,flag=0;
	gets(num);
	cnt1=numCounter1(num);
	cnt3=numCounter2(num);
	for(int i=0;i<strlen(num);i++){
		if(num[i]!='0'&&num[i]!='.'){
			flag=1;
		}
		if(flag&&num[i]!='.'){
			printf("%c",num[i]);
			cnt2++;
		}
		if(cnt2==1&&cnt3!=1&&num[i]!='.'){
			printf(".");
		}
	}
	printf("e%d",cnt1);
	return 0;
}

int numCounter1(char num[]){
	int cnt1=0;
	if(num[0]=='0'){
		for(int i=0;i<strlen(num);i++){
			if(num[i]=='.')continue;
			else if(num[i]=='0')cnt1++;
			else if(num[i]!='0')break;
			}
			cnt1=-cnt1;
		}
	else{
		for(int i=0;i<strlen(num);i++){
			if(num[i]=='.'){
				break;
			}
			cnt1++;
		}
		cnt1--;
	}
	return cnt1;
}

int numCounter2(char num[]){
	int cnt3=0,i;
	for(i=0;i<strlen(num);i++){
		if(num[i]!='0'&&num[i]!='.'){
			break;
		}
	}
	for(;i<strlen(num);i++){
		if(num[i]!='.'){
			cnt3++;
		}
	}
	return cnt3;
}


