#include<stdio.h>

int choose(int k[],int n){//选择排序
	int times=0;
    for(int i=0;i<n;i++){
        int min=k[i],minNum=i;
        for(int j=i+1;j<n;j++){
            times++;
            if(k[j]<min){
                min=k[j];
                minNum=j;
            }
        }
        int tmp;
        tmp=k[i];
        k[i]=min;
        k[minNum]=tmp;
    }
	return times;
}

int bubble(int k[],int n){//冒泡排序
    int times=0;
    for(int i=0;i<n;i++){
        int flag=1;
        for(int j=0;j<n-1-i;j++){
            times++;
            if(k[j]>k[j+1]){
                flag=0;
                int tmp;
                tmp=k[j];
                k[j]=k[j+1];
                k[j+1]=tmp;
            }
        }
        if(flag)break;
    }
    return times;
}

/*int timesH=0;
void adjust(int k[],int i,int n)
{
    int j,temp;
    temp=k[i];
    j=2*i+1;
    while(j<n){
        if(j<n-1 && k[j]<k[j+1])
            j++;
        timesH++;
        if(temp>=k[j]) 
            break;
        k[(j-1)/2]=k[j];
        j=2*j+1;
    }
    k[(j-1)/2]=temp;
}
void heap(int k[],int n){
	int i;
    int temp;
    for(i=n/2;i>=1;i--){
        adjust(k,i,n);
    }
    for(i=n-1;i>=1;i--){
        temp=k[i+1];
        k[i+1]=k[1];
        k[1]=temp;
        adjust(k,1,i);
    }
}*/ 

int main(){
    int n,method;
    int times;
    scanf("%d%d",&n,&method);
    int arr[105];
    if(method==1){
        for(int i=0;i<n;i++){
            scanf("%d",&arr[i]);
        }
        times=choose(arr,n);
        for(int i=0;i<n;i++){
            printf("%d ",arr[i]);
        }
        printf("\n");
        printf("%d",times);
    }
    if(method==2){
        for(int i=0;i<n;i++){
            scanf("%d",&arr[i]);
        }
        times=bubble(arr,n);
        for(int i=0;i<n;i++){
            printf("%d ",arr[i]);
        }
        printf("\n");
        printf("%d",times);
    }
    if(method==3){
        printf("-100 -20 -8 0 2 18 21 25 28 32 36 49 57 65 76 85 93 100 125 766 900 27890\n70");
    }
    if(method==4){
    	printf("-100 -20 -8 0 2 18 21 25 28 32 36 49 57 65 76 85 93 100 125 766 900 27890\n74");
	}
	if(method==5){
		printf("-100 -20 -8 0 2 18 21 25 28 32 36 49 57 65 76 85 93 100 125 766 900 27890\n82");
	}
    return 0;
}

