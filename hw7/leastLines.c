#define infinity 9999
#include<stdio.h>
#include<stdlib.h>

typedef struct node1{
    int edgeNum;
    int point;
    int weight;
    struct node1* next;
}edge,*edgePtr;

typedef struct node2{
    edgePtr next;
}point;

point points[105];
int known[105]={0};
int lowCost[105],edges[105];

int main(){
    int numOfEdge,numOfPoint;
    scanf("%d%d",&numOfPoint,&numOfEdge);
    for(int i=0;i<numOfEdge;i++){
        int e,v1,v2,weight;
        edgePtr p,p1;
        scanf("%d%d%d%d",&e,&v1,&v2,&weight);
        if(points[v1].next==NULL){
            p=(edgePtr)malloc(sizeof(edge));
            points[v1].next=p;
            p->next=NULL;
            p->point=v2;
            p->edgeNum=e;
            p->weight=weight;
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
            p->weight=weight;
        }
        if(points[v2].next==NULL){
            p=(edgePtr)malloc(sizeof(edge));
            points[v2].next=p;
            p->next=NULL;
            p->point=v1;
            p->edgeNum=e;
            p->weight=weight;
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
            p->weight=weight;
        }
    }
    for(int i=0;i<numOfPoint;i++){
        lowCost[i]=infinity;
        edges[i]=0;
    }
    int flag=1;//标示出循环状态；
    int s=0;
    known[s]=1;
    lowCost[s]=0;
    while(flag){
        edgePtr p=NULL;
        p=points[s].next;
        while(p!=NULL){
            if(!known[p->point]){
                if(p->weight<lowCost[p->point]){
                    lowCost[p->point]=p->weight;
                    edges[p->point]=p->edgeNum;
                }
            }
            p=p->next;
        }
        int trig=1;
        int minOrder,min;
        for(int i=0;i<numOfPoint;i++){
            if(trig){
                if(known[i]==0){
                    minOrder=i,min=lowCost[i];
                    trig=0;
                }
            }
            if(lowCost[i]<min&&known[i]==0){
                minOrder=i;
                min=lowCost[i];
            }
        }
        known[minOrder]=1;
        s=minOrder;
        flag=0;
        for(int i=0;i<numOfPoint;i++){
            if(known[i]==0){
                flag=1;
                break;
            }
        }
    }

    int sum=0;
    for(int i=0;i<numOfPoint;i++){
        sum+=lowCost[i];
    }
    printf("%d\n",sum);
    for(int i=0;i<numOfPoint;i++){
        for(int j=0;j<numOfPoint-1;j++){
            if(edges[j]>edges[j+1]){
                int tmp=edges[j];
                edges[j]=edges[j+1];
                edges[j+1]=tmp;
            }
        }
    }
    for(int i=1;i<numOfPoint;i++){
        printf("%d ",edges[i]);
    }
    return 0;
}

