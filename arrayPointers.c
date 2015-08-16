#include<stdio.h>
int main(){
	int sample[][2]={
		{1234,56},
		{1235,67},
		{1236,78},
		{1237,89},
	};
	int (*p)[2];
	int i,*pint,j;
	for(i=0;i<4;i++){
		p=sample[i];
		printf("%p %p\n",sample[i],&sample[i]);
		pint=(int *)p;
		for(j=0;j<2;j++){
			printf("%d\t",*(pint+j));
		}
		printf("\n");

	}
}
