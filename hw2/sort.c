#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<math.h>
#define MAX(x,y) (x>y)?x:y
#define MIN(x,y) (x<y)?x:y

typedef struct{
	char name[20];
	long long phoneNum;
	int flag;
}people;

int main()
{
	people group[100],tem;
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%s %lld",group[i].name,&group[i].phoneNum);
		group[i].flag=1;
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n-1;j++){
			if(strcmp(group[j].name,group[j+1].name)>0){
				tem=group[j];
				group[j]=group[j+1];
				group[j+1]=tem;
			}
		}
	}
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			if(group[j].phoneNum==group[i].phoneNum){
				group[j].flag=0;
			}
			if(strcmp(group[j].name,group[i].name)!=0){
				break;
			}
		}
	}
	int cnt=0;
	for(int i=0;i<n;i++){
		if(group[i].flag==0){
			continue;
		}
		if(i!=0&&strcmp(group[i].name,group[i-1].name)==0){
			cnt++;
		}
		else if(i!=0&&strcmp(group[i].name,group[i-1].name)!=0){
			cnt=0;
		}
		if(cnt==0){
			printf("%s %lld\n",group[i].name,group[i].phoneNum);
		}
		else{
			printf("%s_%d %lld\n",group[i].name,cnt,group[i].phoneNum);
		}
	}
	return 0;
}


