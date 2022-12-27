#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    struct node* lChild;
    struct node* rChild;
    int num;
}tNode,*tLink;

tLink creatTree(){
    tLink root=NULL;
    tLink p=NULL,tmpp=NULL;
    int n,tmp;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&tmp);
        if(root==NULL){
            p=(tLink)malloc(sizeof(tNode));
            p->lChild=NULL;
            p->rChild=NULL;
            p->num=tmp;
            root=p;
        }
        else{
            p=root;
			while(p!=NULL){
                tmpp=p;
                if(tmp>=p->num){
                    p=p->rChild;
                }
                else if(tmp<p->num){
                    p=p->lChild;
                }
            }
            p=(tLink)malloc(sizeof(tNode));
            p->lChild=NULL;
            p->rChild=NULL;
            p->num=tmp;
            if(tmp>tmpp->num){
                tmpp->rChild=p;
            }else{
                tmpp->lChild=p;
            }
        }
    }
    return root;
}

void traverseTree(tLink root,int depth){
    tLink p=root;
    if(p==NULL)return;
    if(p->lChild==NULL&&p->rChild==NULL){
        printf("%d %d\n",p->num,depth);
    }
    traverseTree(p->lChild,depth+1);
    traverseTree(p->rChild,depth+1);
}

int main(){
    tLink root=NULL;
    root=creatTree();
    traverseTree(root,1);
    return 0;
}

