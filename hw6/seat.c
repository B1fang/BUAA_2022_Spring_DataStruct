#include<stdio.h>
#include<string.h>

typedef struct{
    int num;
    char name[100];
    int seatNum;
}student;

student students[105];
int stuPtr=0;

int min(int x,int y){
    if(x>y)return y;
    return x;
}

int main(){
    int n;
    scanf("%d",&n);
	FILE* input=fopen("in.txt","r");
    FILE* output=fopen("out.txt","w");
    while(fscanf(input,"%d %s %d",&students[stuPtr].num,students[stuPtr].name,&students[stuPtr].seatNum)!=EOF){
        stuPtr++;
	}
    for(int i=0;i<stuPtr;i++){
    	for(int j=0;j<stuPtr-1;j++){
    		if(students[j].seatNum>students[j+1].seatNum){
                student tmp;
                tmp=students[j];
                students[j]=students[j+1];
                students[j+1]=tmp;
            }
		}
	}
    int q=min(n,students[stuPtr-1].seatNum);
    int hush[105]={0};
    for(int i=0;i<stuPtr;i++){
        if(students[i].seatNum>q)break;
        hush[students[i].seatNum]++;
    }
    int tmpPtr=stuPtr-1;
    int max;
    for(int i=1;i<=q;i++){
        if(hush[i]==0){
            students[tmpPtr--].seatNum=i;
        }
        max=0;
        for(int j=0;j<stuPtr;j++){
            if(students[j].seatNum>max){
                max=students[j].seatNum;
            }
        }
        q=min(n,max);
    }
    for(int i=0;i<stuPtr;i++){
    	for(int j=0;j<stuPtr-1;j++){
    		if(students[j].seatNum>students[j+1].seatNum){
                student tmp;
                tmp=students[j];
                students[j]=students[j+1];
                students[j+1]=tmp;
            }
		}
	}
    int m=students[stuPtr-1].seatNum+1;
    for(int i=0;i<stuPtr-1;i++){
        if(students[i].seatNum==students[i+1].seatNum){
            students[i+1].seatNum=m;
            m++;
        }
    }
    for(int i=0;i<stuPtr;i++){
    	for(int j=0;j<stuPtr-1;j++){
    		if(students[j].num>students[j+1].num){
                student tmp;
                tmp=students[j];
                students[j]=students[j+1];
                students[j+1]=tmp;
            }
		}
	}
    for(int i=0;i<stuPtr;i++){
        fprintf(output,"%d %s %d\n",students[i].num,students[i].name,students[i].seatNum);
    }
	fclose(input);
    fclose(output);
    return 0;
}

