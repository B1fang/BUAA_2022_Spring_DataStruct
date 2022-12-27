#include<stdio.h>
#include<stdlib.h>

//int dataSave[100][100]={{0},{0}};

typedef struct tnode{
    int orderNum;
    int weight;
    struct tnode * lChild;
    struct tnode * midChild;
    struct tnode * rChild;
}tNode , *tPtr;

typedef struct {
    int orderNum;
    int weight;
}leaf;

int cnt1[100]={0};
leaf leaves[100][100];

tPtr findNode(tPtr root , int target);
void traverse(tPtr root , int depth);

int main(){
    int target=0,cnt=0;
    int leafCnt=0;
    int tmpArr[4]={0},arrCnt=0;;
    tPtr inputPtr=NULL,root=NULL;
    tPtr ptr1=NULL,ptr2=NULL,ptr3=NULL;
    while(1){//这一段代码用于构建树
        scanf("%d",&target);
        if(target==-1)break;
        if(cnt==0){
            root=(tPtr)malloc(sizeof(tNode));
            root->lChild=NULL;
            root->midChild=NULL;
            root->rChild=NULL;
            root->orderNum=target;
            cnt++;
        }
        inputPtr=findNode(root,target);//这里函数调用有问题
/*        if(!inputPtr){
            printf("flag1!");
            return 0;
        }*/
        arrCnt=0;
        while(1){
            scanf("%d",&tmpArr[arrCnt++]);
            if(tmpArr[arrCnt-1]==-1){
                arrCnt--;
                break;
            }
            if(tmpArr[arrCnt-1]<100)leafCnt++;
        }
        if(arrCnt==1){
            ptr1=(tPtr)malloc(sizeof(tNode));
            ptr1->orderNum=tmpArr[0];
            ptr1->lChild=NULL;
            ptr1->midChild=NULL;
            ptr1->rChild=NULL;
            inputPtr->lChild=ptr1;
        }
        if(arrCnt==2){
            ptr1=(tPtr)malloc(sizeof(tNode));
            ptr1->orderNum=tmpArr[0];
            ptr1->lChild=NULL;
            ptr1->midChild=NULL;
            ptr1->rChild=NULL;
            ptr3=(tPtr)malloc(sizeof(tNode));
            ptr3->orderNum=tmpArr[1];
            ptr3->lChild=NULL;
            ptr3->midChild=NULL;
            ptr3->rChild=NULL;
            inputPtr->lChild=ptr1;
            inputPtr->rChild=ptr3;
        }
        else if(arrCnt==3){
            ptr1=(tPtr)malloc(sizeof(tNode));
            ptr1->orderNum=tmpArr[0];
            ptr1->lChild=NULL;
            ptr1->midChild=NULL;
            ptr1->rChild=NULL;
            ptr2=(tPtr)malloc(sizeof(tNode));
            ptr2->orderNum=tmpArr[1];
            ptr2->lChild=NULL;
            ptr2->midChild=NULL;
            ptr2->rChild=NULL;
            ptr3=(tPtr)malloc(sizeof(tNode));
            ptr3->orderNum=tmpArr[2];
            ptr3->lChild=NULL;
            ptr3->midChild=NULL;
            ptr3->rChild=NULL;
            inputPtr->lChild=ptr1;
            inputPtr->midChild=ptr2;
            inputPtr->rChild=ptr3;
        }
    }
    int target1,weight;
    for(int i=0;i<leafCnt;i++){
        scanf("%d%d",&target1,&weight);
        inputPtr=findNode(root,target1);
/*        if(!inputPtr){
            printf("flag2!");
            return 0;
        }*/
        inputPtr->weight=weight;
    }
    traverse(root,0);
    leaf tmpLeaves1[1000];
    leaf tmpLeaves2[1000];
    int tmpCnt=0;
    for(int i=0;i<100;i++){
        if(cnt1[i]>0){
            for(int j=0;j<cnt1[i];j++){
                tmpLeaves1[tmpCnt].orderNum=leaves[i][j].orderNum;
                tmpLeaves1[tmpCnt].weight=leaves[i][j].weight;
                tmpLeaves2[tmpCnt].orderNum=leaves[i][j].orderNum;
                tmpLeaves2[tmpCnt].weight=leaves[i][j].weight;
                tmpCnt++;
            }
        }
    }
    leaf tmpSt;
    for(int i=0;i<tmpCnt;i++){
        for(int j=0;j<tmpCnt-1;j++){
            if(tmpLeaves1[j].weight<tmpLeaves1[j+1].weight){
                tmpSt=tmpLeaves1[j];
                tmpLeaves1[j]=tmpLeaves1[j+1];
                tmpLeaves1[j+1]=tmpSt;
            }
            else if(tmpLeaves1[j].weight==tmpLeaves1[j+1].weight){
                if(tmpLeaves1[j].orderNum>tmpLeaves1[j+1].orderNum){
                    tmpSt=tmpLeaves1[j];
                    tmpLeaves1[j]=tmpLeaves1[j+1];
                    tmpLeaves1[j+1]=tmpSt;
                }
            }
        }
    }
    for(int i=0;i<tmpCnt;i++){
        printf("%d->%d\n",tmpLeaves1[i].orderNum,tmpLeaves2[i].orderNum);
    }
    return 0;
}

tPtr findNode(tPtr root , int target){//根据给定关键字查找节点的函数
	if(root==NULL)return NULL;
	tPtr p=root;
	if(p->orderNum==target)return p;
    p=findNode(root->lChild,target);
    if(p!=NULL)return p;
    p=findNode(root->midChild,target);
    if(p!=NULL)return p;
    p=findNode(root->rChild,target);
    return p;
}
void traverse(tPtr root , int depth){
    if(root==NULL)return;
	tPtr p=root;
    if(p->orderNum<100){
        leaves[depth][cnt1[depth]].orderNum=p->orderNum;
        leaves[depth][cnt1[depth]++].weight=p->weight;
    }
    traverse(root->lChild,depth+1);
    traverse(root->midChild,depth+1);
    traverse(root->rChild,depth+1);
}



