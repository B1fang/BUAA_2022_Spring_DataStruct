#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node1{
    int point;
    char edgeNum;
    struct node1*next;
}edge,*edgePtr;
typedef struct node2{
    edgePtr next;
}point;

point points[1005];
int visited[1005]={0};

typedef struct {
    char rot[100];
}route;
route routes[100];
int routePtr=0;

void DFS(int s,int e,char tmpRoute[],int length){
    if(s==e){
        tmpRoute[length]='\0';
        strcpy(routes[routePtr++].rot,tmpRoute);
        return;
    }
    if(visited[s])return;
    visited[s]=1;
    edgePtr p=points[s].next;
    while(p!=NULL){
        if(!visited[p->point]){
            tmpRoute[length]=p->edgeNum;
            DFS(p->point,e,tmpRoute,length+1);
        }
        p=p->next;
    }
    visited[s]=0;
}

int main(){
    int numOfPoint,numOfEdge;
    char tmpRoute[100]="";
    scanf("%d%d",&numOfPoint,&numOfEdge);
    for(int i=0;i<1005;i++){
        points[i].next=NULL;
    }
    for(int i=0;i<numOfEdge;i++){
        int e;
		int v1,v2;
        edgePtr p=NULL,p1=NULL;
        scanf("%d%d%d",&e,&v1,&v2);
        if(points[v1].next==NULL){
            p=(edgePtr)malloc(sizeof(edge));
            points[v1].next=p;
            p->next=NULL;
            p->point=v2;
            p->edgeNum=e;
        }
        else{
            p=(edgePtr)malloc(sizeof(edge));
            p->next=NULL;
            p->point=v2;
            p->edgeNum=e;
            p1=points[v1].next;
            while(p1->next!=NULL){
                p1=p1->next;
            }
            p1->next=p;
        }
        if(points[v2].next==NULL){
            p=(edgePtr)malloc(sizeof(edge));
            points[v2].next=p;
            p->next=NULL;
            p->point=v1;
            p->edgeNum=e;
        }
        else{
            p=(edgePtr)malloc(sizeof(edge));
            p->next=NULL;
            p->point=v1;
            p->edgeNum=e;
            p1=points[v2].next;
            while(p1->next!=NULL){
                p1=p1->next;
            }
            p1->next=p;
        }
    }
    DFS(0,numOfPoint-1,tmpRoute,0);
    for(int i=0;i<routePtr;i++){
        for(int j=0;j<routePtr-1;j++){
            if(strcmp(routes[j].rot,routes[j+1].rot)>0){
                route tmp;
                tmp=routes[j];
                routes[j]=routes[j+1];
                routes[j+1]=tmp;
            }
        }
    }
    for(int i=0;i<routePtr;i++){
        for(int j=0;routes[i].rot[j]!='\0';j++){
            printf("%d ",routes[i].rot[j]);
        }
        printf("\n");
    }
    return 0;
}

