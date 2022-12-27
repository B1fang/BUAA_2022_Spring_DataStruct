/*
 *树的遍历采取中序遍历
 *需要用到对树的操作：查找节点，（若无）添加节点
 *排序的关键字：字典序（使用strcmp实现）
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct treeNode
{
    char word[100];
    int freq;
    struct treeNode * lChild;
    struct treeNode * rChild;
}tNode, *tPtr;

char article[100005];

tPtr findNode(tPtr root,char word[]){
    tPtr p=root;
    while(p!=NULL){
        if(strcmp(word,p->word)==0)return p;
        if(strcmp(word,p->word)<0)p=p->lChild;
        else p=p->rChild;
    }
    return NULL;
}

tPtr insertNode(tPtr root,char word[]){
    tPtr p=root,tmpp=NULL;
    while(p!=NULL){
        tmpp=p;
        if(strcmp(word,p->word)<0)p=p->lChild;
        else p=p->rChild;
    }
    p=(tPtr)malloc(sizeof(tNode));
    p->lChild=NULL;
    p->rChild=NULL;
    strcpy(p->word,word);
    p->freq=1;
    if(strcmp(word,tmpp->word)<0)tmpp->lChild=p;
    else tmpp->rChild=p;
    return root;
}

void bianLi(tPtr root){
    if(root==NULL)return;
    bianLi(root->lChild);
    printf("%s %d\n",root->word,root->freq);
    bianLi(root->rChild);
}

int main(){
    FILE * fp=fopen("article.txt","r");
    fread(article,sizeof(char),100000,fp);
    //实现单词的提取///////////////////////////////////////
    char word[100]="";
    word[0]='\0';
    int wordPtr=0;
    int cnt=0;
    tPtr root=NULL,p=NULL;
    for(int i=0;i<strlen(article);i++){
        if(isalpha(article[i])){
            for(;isalpha(article[i]);i++){
                word[wordPtr++]=towlower(article[i]);
            }
            word[wordPtr]='\0';
            if(cnt==0){
                root=(tPtr)malloc(sizeof(tNode));
                root->lChild=NULL;
                root->rChild=NULL;
                strcpy(root->word,word);
                root->freq=1;
            }
            else{
                p=findNode(root,word);
                if(p==NULL){
                    root=insertNode(root,word);
                }
                else{
                    p->freq++;
                }
            }
            wordPtr=0;
            word[0]='\0';
            cnt++;
        }
    }
    //输出部分/////////////////////////////////////////////
    printf("%s",root->word);
    if(root->rChild!=NULL){
        printf(" ");
        printf("%s",root->rChild->word);
    }
    if(root->rChild->rChild!=NULL){
        printf(" ");
        printf("%s",root->rChild->rChild->word);
    }
    printf("\n");
    bianLi(root);
    fclose(fp);
    return 0;
}



