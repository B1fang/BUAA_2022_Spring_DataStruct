#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<math.h>
#define MAX(x,y) (x>y)?x:y
#define MIN(x,y) (x<y)?x:y

int num[15]={},n;

void printer(int len){
	if(len!=n){
		for(int i=1;i<=n;i++){
			if(check(num,len,i)){
				num[len+1]=i;
				printer(len+1);
			}
		}
	}
	else{
		for(int i=1;i<=n;i++){
			printf("%d ",num[i]);
		}
		printf("\n");
		return ;
	}
}

int check(int num[],int len,int i){
	for(int j=1;j<=len;j++){
		if(num[j]==i)return 0;
	}
	return 1;
}

int main()
{
	scanf("%d",&n);
	printer(0);
	return 0;
}


