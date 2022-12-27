#include<stdio.h>
#include<string.h>
#define MAXNUM 512
#define MAXLEN 30

typedef struct node1{
    char sname[MAXLEN];
    int ischange;
    int parentPoint;
    int line;
}station;

typedef struct node2{
    int wei;
    int lno;
}weight;

typedef struct node3{
    int ischange;
    int line;
    char sname[MAXLEN];
}route;

station BGvertex[MAXNUM];
int numOfStations=0;
weight BGweights[MAXNUM][MAXNUM];

int start,end;

void initMap(){
    FILE* fp=fopen("bgstations.txt","r");
    for(int a=0;a<MAXNUM;a++){
        for(int b=0;b<MAXNUM;b++){
            BGweights[a][b].wei=0;
            BGweights[a][b].lno=0;
        }
    }
    
    int i,j,snum,lno,lnum,v1,v2;
    station st;
    fscanf(fp,"%d",&snum);//总线路数
    for(i=0;i<snum;i++){
        fscanf(fp,"%d %d",&lno,&lnum);//线路序号，站点数量
        v1=v2=-1;//v2代表当前正在处理的顶点的下标，v1则是前序顶点的下标
        for(j=0;j<lnum;j++){
            fscanf(fp,"%s %d",st.sname,&st.ischange);
            for(int k=0;k<numOfStations;k++){
                if(strcmp(st.sname,BGvertex[k].sname)==0){
                    v2=k;
                    goto flag1;
                }
            }
            v2=numOfStations;
            BGvertex[numOfStations++]=st;
            flag1:;
	        if(v1!=-1){//首站无前序顶点
	            BGweights[v1][v2].wei=BGweights[v2][v1].wei=1;
	            BGweights[v1][v2].lno=BGweights[v2][v1].lno=lno;
	        }
	        v1=v2;
        }
    }
    fclose(fp);
}

void bfs(){
    int nowStation=start;
    int visited[MAXNUM]={0};
    int queue[100000]={0};
    int front=0,rear=1;
    visited[start]=1;
    queue[0]=start;
    while(rear>front){
        nowStation=queue[front++];
        for(int i=0;i<MAXNUM;i++){
            if(BGweights[nowStation][i].wei){
                if(visited[i]==0){
                    BGvertex[i].parentPoint=nowStation;
                    BGvertex[i].line=BGweights[nowStation][i].lno;
                    if(i==end){
                        goto flag2;
                    }
                    queue[rear++]=i;
                    visited[i]=1;
                }
            }
        }
    }
    flag2:;
}

int main(){
    initMap();
    char s[100]="",e[100]="";
    gets(s);
    gets(e);
    for(int i=0;i<numOfStations;i++){
        if(strcmp(BGvertex[i].sname,s)==0){
            start=i;
        }
        if(strcmp(BGvertex[i].sname,e)==0){
            end=i;
        }
    }
	bfs();
    int now=end;
    route road[1000];
    int cnt0=0;
    while(now!=start){
        road[cnt0].ischange=BGvertex[now].ischange;
        road[cnt0].line=BGvertex[now].line;
        strcpy(road[cnt0].sname,BGvertex[now].sname);
        cnt0++;
        now=BGvertex[now].parentPoint;
    }
    strcpy(road[cnt0].sname,BGvertex[now].sname);
    int nowLine=road[cnt0-1].line,cnt=0;
    printf("%s",road[cnt0].sname);
    for(int i=cnt0;i>=0;i--){
        if(i==0){
            printf("-%d(%d)-%s",nowLine,cnt,road[i].sname);
            break;
        }
        if(road[i].ischange){
            if(road[i-1].line!=nowLine){
                printf("-%d(%d)-%s",nowLine,cnt,road[i].sname);
                cnt=1;
                nowLine=road[i-1].line;
                continue;
            }
        }
        cnt++;
    }
    return 0;
}



