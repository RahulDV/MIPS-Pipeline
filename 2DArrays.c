#include<stdio.h>
int main(){
	int classRecord[][2]={
		{1234,56},
		{1235,65},
		{1236,76},
		{1237,87},
		{1238,98}
	};
	int i;
	for(i=0;i<=4;i++){
		printf("%p; %d\n",classRecord+i,*classRecord[i]);
	}
	printf("%p\n",classRecord);
}
