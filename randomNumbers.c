#include<time.h>
#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include "randomNumbers.h"
#define STAND_ALONE
#ifndef STAND_ALONE
int main(){
	int i,sample[10];
	generateRandomWeightsArray(sample,10);
	for(i=0;i<10;i++){
		printf("%d\t",sample[i]);
	}
	printf("\nmax = %d\taverage = %d\n",MAX,AVG);
}
#endif

void generateRandomWeightsArray(int* p, int numberOfBoxes){
	int i;
	srand(time(NULL));
	for(i=0;i<numberOfBoxes;i++){
		*p=random()%100;
		printf("%d ",*p);
		p++;
	}
	printf("\n");
}

int getCapacityOfEachTruck(){
	printf("capacity Of each truck = %d\n",100);
	return 100;
}
