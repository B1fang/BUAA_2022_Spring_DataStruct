#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<math.h>
#define MAX(x,y) (x>y)?x:y
#define MIN(x,y) (x<y)?x:y

int mySearch(char row[],char in[],int i){
	char c;
	for(int j=0;j<strlen(in);j++){
		if(isupper(row[i+j])){
			c=tolower(row[j+i]);
		}
		else{
			c=row[j+i];
		}
		if(in[j]!=c){
			return 0;
		}
	}
	return 1;
}

int main()
{
	FILE *fp1,*fp2;
	char row[1024]={0},row1[1024]={0};
	char in[100]={0},out[100]={0};
	fp1=fopen("filein.txt","r");
	fp2=fopen("fileout.txt","w");
	scanf("%s",in);
	scanf("%s",out);
	while(fgets(row,1024,fp1)!=NULL){
		for(int i=0,j=0;i<=strlen(row);i++,j++){
			if(mySearch(row,in,i)==0){
				row1[j]=row[i];
			}
			else if(mySearch(row,in,i)==1){
				for(int k=0;k<strlen(out);k++){
					row1[j+k]=out[k];
				}
				i+=strlen(in)-1;
				j+=strlen(out)-1;
			}
		}
		fputs(row1,fp2);
		memset(row,0,sizeof(row));
		memset(row1,0,sizeof(row1));
	}
	fclose(fp1);
	fclose(fp2);
	return 0;
}



