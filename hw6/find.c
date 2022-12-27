#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define NHASH 3001
#define MULT 37
#define MAXN 3500

unsigned int hash(char *str)
{
    unsigned int h=0;
    char *p=NULL;
    for(p=str; *p!='\0'; p++)
        h = MULT*h + *p;
    return (h % NHASH);
}

typedef struct node{
    char word[30];
    struct node* next;
}hNode,*hLink;

char dictionary[3500][30];
int dicPtr=0;
int index[26][2]={{0},{0}};
hLink hushTab[NHASH]={NULL};

int main(){
    FILE* fp=fopen("dictionary3000.txt","r");
    char buffer[30]="";
    while(fscanf(fp,"%s",buffer)!=EOF){
        if(strlen(buffer)==0)continue;
        /////////////////////////////////////构建索引 
		if(buffer[0]!='a'){
        	if(index[buffer[0]-'a'][0]==0){
        		index[buffer[0]-'a'][0]=dicPtr;
			}
		}
        index[buffer[0]-'a'][1]=dicPtr;
        /////////////////////////////////////构建hush表
        unsigned int hush=hash(buffer); 
        if(hushTab[hush]==NULL){
            hLink p=(hLink)malloc(sizeof(hNode));
            strcpy(p->word,buffer);
            hushTab[hush]=p;
            p->next=NULL;
        }
        else{
            hLink p=(hLink)malloc(sizeof(hNode));
            strcpy(p->word,buffer);
            p->next=NULL;
            hLink tmp=hushTab[hush];
            while(tmp->next!=NULL){
                tmp=tmp->next;
            }
            tmp->next=p;
        }
        //////////////////////////////////////////////
        strcpy(dictionary[dicPtr++],buffer);
    }
    fclose(fp);
    int op;
    scanf("%s %d",buffer,&op);
    if(op==1){
        for(int i=0;i<dicPtr;i++){
            if(strcmp(dictionary[i],buffer)==0){
                printf("1 %d",i+1);
                goto flag1;
            }
            else if(strcmp(dictionary[i],buffer)>0){
                printf("0 %d",i+1);
                goto flag1;
            }
        }
        printf("0 %d",dicPtr);
        flag1:;
    }
    else if(op==2){
    	int left=0,right=dicPtr-1;
        int cnt=0;
        while(left<=right){
            int mid=(left+right)/2;
            cnt++;
            if(strcmp(buffer,dictionary[mid])==0){
                printf("1 %d",cnt);
                goto flag2;
            }
            else if(strcmp(buffer,dictionary[mid])>0){
                left=mid+1;
            }
            else{
                right=mid-1;
            }
        }
        printf("0 %d",cnt);
        flag2:;
	}
	else if(op==3){
		int left=index[buffer[0]-'a'][0],right=index[buffer[0]-'a'][1];
        int cnt=0;
        if(left==right){
            printf("0 0");
            goto flag3;
        }
        while(left<=right){
            int mid=(left+right)/2;
            cnt++;
            if(strcmp(buffer,dictionary[mid])==0){
                printf("1 %d",cnt);
                goto flag3;
            }
            else if(strcmp(buffer,dictionary[mid])>0){
                left=mid+1;
            }
            else{
                right=mid-1;
            }
        }
        printf("0 %d",cnt);
        flag3:;
	}
	else if(op==4){
		unsigned int hush1=hash(buffer);
        int cnt=0;
        if(hushTab[hush1]==NULL){
            printf("0 0");
            goto flag4;
        }
        else{
            hLink p1=hushTab[hush1];
            while(p1!=NULL){
                cnt++;
                if(strcmp(p1->word,buffer)==0){
                    printf("1 %d",cnt);
                    goto flag4;
                }
                else if(strcmp(p1->word,buffer)>0){
                    printf("0 %d",cnt);
                    goto flag4;
                }
                p1=p1->next;
            }
        }
        printf("0 %d",cnt);
        flag4:;
    }
    return 0;
}

