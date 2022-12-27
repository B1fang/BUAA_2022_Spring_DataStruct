#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<math.h>
#define MAX(x,y) (x>y)?x:y
#define MIN(x,y) (x<y)?x:y
int main(){
	char string[200]="";
	scanf("%s",string);
	int j,tru=1;
	for(int i=0;i<strlen(string);i++){
		if(string[i]=='-'){
			if(isdigit(string[i-1])&&isdigit(string[i+1])){
				j=1,tru=0;
				while(string[i-1]+j<string[i+1]){
					printf("%c",string[i-1]+j);
					j++;
				}
			}
			else if(isupper(string[i-1])&&isupper(string[i+1])){
				j=1,tru=0;
				while(string[i-1]+j<string[i+1]){
					printf("%c",string[i-1]+j);
					j++;
				}
			}
			else if(islower(string[i-1])&&islower(string[i+1])){
				j=1,tru=0;
				while(string[i-1]+j<string[i+1]){
					printf("%c",string[i-1]+j);
					j++;
				}
			}
		}
		if(tru){
			printf("%c",string[i]);
		}
		tru=1;
		
	}
	return 0;
}

