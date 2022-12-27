#include<stdio.h>
#include<string.h>

int graph[105][105]={{0},{0}};
int visited[105]={0};
int state[105]={0};
int deleteP;
int queue[200]={0};
int front=0,rear=0;

void DFS(int s){
    printf("%d ",s);
    visited[s]=1;
    for(int i=0;i<105;i++){
        if(graph[s][i]==0||visited[i]||state[i])continue;
        DFS(i);
    }
}

void BFS(int s){
	printf("%d ",s);
    visited[s]=1;
    queue[rear++]=s;
    int r;
    while(front!=rear){
        r=queue[front++];
        for(int c=0;c<105;c++){
            if(graph[r][c]==0||visited[c]||state[c])continue;
            printf("%d ",c);
            queue[rear++]=c;
            visited[c]=1;
        }
    }
}

int main(){
    int numOfPoint,numOfEdge;
    scanf("%d%d",&numOfPoint,&numOfEdge);
    for(int i=0;i<numOfEdge;i++){
        int p1,p2;
        scanf("%d%d",&p1,&p2);
        graph[p1][p2]=1;
        graph[p2][p1]=1;
    }
    scanf("%d",&deleteP);
	memset(visited,0,sizeof(visited));
    DFS(0);
    printf("\n");
    memset(visited,0,sizeof(visited));
    BFS(0);
    printf("\n");
    state[deleteP]=1;
    memset(visited,0,sizeof(visited));
    DFS(0);
    printf("\n");
    memset(visited,0,sizeof(visited));
    BFS(0);
    printf("\n");
    return 0;
}

