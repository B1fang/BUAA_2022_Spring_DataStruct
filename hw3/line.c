#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<math.h>
#define MAX(x,y) (x>y)?x:y
#define MIN(x,y) (x<y)?x:y

typedef struct {
	int x1,y1;
	int x2,y2;
	int flag;
}line;

int main()
{
	line lines[105],tmp;
	int n,cnt,ccnt=0,xmax,ymax;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d%d%d%d",&lines[i].x1,&lines[i].y1,&lines[i].x2,&lines[i].y2);
		lines[i].flag=0;
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n-1;j++){
			if(lines[j].x1>lines[j+1].x1){
				tmp=lines[j];
				lines[j]=lines[j+1];
				lines[j+1]=tmp;
			}
		}
	}
	for(int i=0;i<n;i++){
		if(lines[i].flag){
			continue;
		}
		int m=lines[i].x2,n0=lines[i].y2;
		cnt=1;
		for(int j=i+1;j<n;j++){
			if((lines[j].x1==m)&&(lines[j].y1==n0)){
				cnt++;
				m=lines[j].x2,n0=lines[j].y2;
				lines[j].flag=1;
			}
		}
		if(cnt>ccnt){
			ccnt=cnt;
			xmax=lines[i].x1;
			ymax=lines[i].y1;
		}
	}
	printf("%d %d %d",ccnt,xmax,ymax);
	return 0;
}


