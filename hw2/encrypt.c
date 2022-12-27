#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<math.h>
#define MAX(x,y) (x>y)?x:y
#define MIN(x,y) (x<y)?x:y
int main()
{
	int alphaBet[26]={0};
	char key1[51]={0},key[26]={0};
	scanf("%s",key1);
	for(int i=0;i<strlen(key1);i++){
		alphaBet[key1[i]-'a']=1;
	}
	for(int i=0;i<26;i++){
		if(alphaBet[i]==0){
			alphaBet[i]=2;
		}
	}
	int j=0;
	for(int i=0;i<26;i++){
		if(alphaBet[key1[i]-'a']==2){
			continue;
		}
		else if(alphaBet[key1[i]-'a']==1){
			key[j++]=key1[i];
			alphaBet[key1[i]-'a']--;
		}
	}
	for(int k=25;k>=0;k--){
		if(alphaBet[k]==2){
			key[j++]=k+'a';
		}
	}//此时key数组为密钥 
	FILE *fp1,*fp2;
	fp1=fopen("encrypt.txt","r");
	fp2=fopen("output.txt","w");
	char c;
	while((c=getc(fp1))!=EOF){
		if(isalpha(c)){
			c=key[c-'a'];
			putc(c,fp2);
		}
		else{
			putc(c,fp2);
		}
	}
	fclose(fp1);
	fclose(fp2);
	return 0;
}




