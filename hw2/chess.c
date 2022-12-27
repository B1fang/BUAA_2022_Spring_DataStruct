#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<math.h>
#define MAX(x,y) (x>y)?x:y
#define MIN(x,y) (x<y)?x:y

int main()
{
	int table[19][19]={{0},{0}};
	for(int i=0;i<19;i++){
		for(int j=0;j<19;j++){
			scanf("%d",&table[i][j]);
		}
	}
	for(int i=0;i<19;i++){//行遍历 
		for(int j=0;j<15;j++){
			if(table[i][j]==1&&table[i][j+1]==1&&table[i][j+2]==1&&table[i][j+3]==1){
				if(j==0){
					if(table[i][j+4]==0){
						printf("1:%d,%d",i+1,j+1);
						goto flag1;
					}
				}
				else if(j+3==18){
					if(table[i][j-1]==0){
						printf("1:%d,%d",i+1,j+1);
						goto flag1;
					}
				}
				else{
					if(table[i][j-1]==0||table[i][j+4]==0){
						printf("1:%d,%d",i+1,j+1);
						goto flag1;
					}
				}
			}
			if(table[i][j]==2&&table[i][j+1]==2&&table[i][j+2]==2&&table[i][j+3]==2){
				if(j==0){
					if(table[i][j+4]==0){
						printf("2:%d,%d",i+1,j+1);
						goto flag1;
					}
				}
				else if(j+3==18){
					if(table[i][j-1]==0){
						printf("2:%d,%d",i+1,j+1);
						goto flag1;
					}
				}
				else{
					if(table[i][j-1]==0||table[i][j+4]==0){
						printf("2:%d,%d",i+1,j+1);
						goto flag1;
					}
				}
			}
		}
	}
	for(int j=0;j<19;j++){//列遍历 
		for(int i=0;i<15;i++){
			if(table[i][j]==1&&table[i+1][j]==1&&table[i+2][j]==1&&table[i+3][j]==1){
				if(i==0){
					if(table[i+4][j]==0){
						printf("1:%d,%d",i+1,j+1);
						goto flag1;
					}
				}
				else if(i+3==18){
					if(table[i-1][j]==0){
						printf("1:%d,%d",i+1,j+1);
						goto flag1;
					}
				}
				else{
					if(table[i-1][j]==0||table[i+4][j]==0){
						printf("1:%d,%d",i+1,j+1);
						goto flag1;
					}
				}
			}
			if(table[i][j]==2&&table[i+1][j]==2&&table[i+2][j]==2&&table[i+3][j]==2){
				if(i==0){
					if(table[i+4][j]==0){
						printf("2:%d,%d",i+1,j+1);
						goto flag1;
					}
				}
				else if(i+3==18){
					if(table[i-1][j]==0){
						printf("2:%d,%d",i+1,j+1);
						goto flag1;
					}
				}
				else{
					if(table[i-1][j]==0||table[i+4][j]==0){
						printf("2:%d,%d",i+1,j+1);
						goto flag1;
					}
				}
			}
		}
	}
	for(int i=4;i<19;i++){//对角线遍历1 
		int i0=i;
		for(int j=0;j+3<=i;j++,i0--){
			if(table[i0][j]==1&&table[i0-1][j+1]==1&&table[i0-2][j+2]==1&&table[i0-3][j+3]==1){
				if(i0==i){
					if(table[i0-4][j+4]==0){
						printf("1:%d,%d",i0-3+1,j+3+1);
						goto flag1;
					}
				}
				else if(i0-3==0){
					if(table[i0+1][j-1]==0){
						printf("1:%d,%d",i0-3+1,j+3+1);
						goto flag1;
					}
				}
				else{
					if(table[i0+1][j-1]==0||table[i0-4][j+4]==0){
						printf("1:%d,%d",i0-3+1,j+3+1);
						goto flag1;
					}
				}
			}
			if(table[i0][j]==2&&table[i0-1][j+1]==2&&table[i0-2][j+2]==2&&table[i0-3][j+3]==2){
				if(i0==i){
					if(table[i0-4][j+4]==0){
						printf("2:%d,%d",i0-3+1,j+3+1);
						goto flag1;
					}
				}
				else if(i0-3==0){
					if(table[i0+1][j-1]==0){
						printf("2:%d,%d",i0-3+1,j+3+1);
						goto flag1;
					}
				}
				else{
					if(table[i0+1][j-1]==0||table[i0-4][j+4]==0){
						printf("2:%d,%d",i0-3+1,j+3+1);
						goto flag1;
					}
				}
			}
		}
	}
	for(int j=0;j<15;j++){//对角线遍历2 
		int j0=j;
		for(int i=18;i-3>=j;i--,j0++){
			if(table[i][j0]==1&&table[i-1][j0+1]==1&&table[i-2][j0+2]==1&&table[i-3][j0+3]==1){
				if(i==18){
					if(table[i+4][j0+4]==0){
						printf("1:%d,%d",i-3+1,j0+3+1);
						goto flag1;
					}
				}
				else if(j0+3==18){
					if(table[i+1][j-1]==0){
						printf("1:%d,%d",i-3+1,j0+3+1);
						goto flag1;
					}
				}
				else{
					if(table[i+4][j0+4]==0||table[i+1][j-1]==0){
						printf("1:%d,%d",i-3+1,j0+3+1);
						goto flag1;
					}
				}
			}
			else if(table[i][j0]==2&&table[i-1][j0+1]==2&&table[i-2][j0+2]==2&&table[i-3][j0+3]==2){
				if(i==18){
					if(table[i+4][j0+4]==0){
						printf("2:%d,%d",i-3+1,j0+3+1);
						goto flag1;
					}
				}
				else if(j0+3==18){
					if(table[i+1][j-1]==0){
						printf("2:%d,%d",i-3+1,j0+3+1);
						goto flag1;
					}
				}
				else{
					if(table[i+4][j0+4]==0||table[i+1][j-1]==0){
						printf("2:%d,%d",i-3+1,j0+3+1);
						goto flag1;
					}
				}
			}
		}
	}
	printf("1:2,2");
	flag1:;
	return 0;
}


