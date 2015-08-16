#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "randomNumbers.h"
struct sumOfWeights{
	int value;
	struct weight* head;
	struct sumOfWeights* next;
};

struct weight{
	int weightValue;
	struct weight* next;
};
struct sumOfWeights* deleteBigNodes(struct sumOfWeights* head, int capacityOfEachTruck);
struct sumOfWeights* mergeLists(struct sumOfWeights* list1,struct sumOfWeights* list2);
void approximateBinPackingSolution(int numberOfBoxes, int* weightOfBox, int capacityOfEachTruck);
void optimalBinPackingSolution(int numberOfBoxes, int* weightOfBox, int capacityOfEachTruck);
int main(){
	clock_t begin, end;
	double timeSpent;
	int numberOfBoxes;
	printf("Enter the number of boxes\n");
	scanf("%d",&numberOfBoxes);
	int weightOfBox[numberOfBoxes];
	int capacityOfEachTruck;
	generateRandomWeightsArray(weightOfBox,numberOfBoxes);
	capacityOfEachTruck=getCapacityOfEachTruck();
	begin=clock();
	approximateBinPackingSolution(numberOfBoxes, weightOfBox, capacityOfEachTruck);
	end=clock();
	timeSpent = (double)(end-begin)/CLOCKS_PER_SEC;
	printf("approximate alg execution time : %lf\n",timeSpent);
	begin=clock();
	optimalBinPackingSolution(numberOfBoxes, weightOfBox, capacityOfEachTruck);
	end=clock();
	timeSpent = (double)(end-begin)/CLOCKS_PER_SEC;
	printf("optimal alg execution time : %lf\n",timeSpent);
	return 0; 
}

void approximateBinPackingSolution(int numberOfBoxes, int* weightOfBox, int capacityOfEachTruck){
	printf("Approximate Solution starts here\n");
	int sum=0,i,numberOfTrucks=0;
	struct weight* temp=NULL;
	for(i=0;i<numberOfBoxes;i++){
		sum=sum + *(weightOfBox+i);
		struct weight* boxWeight=malloc(sizeof(struct weight));
		boxWeight->weightValue= *(weightOfBox+i);
		boxWeight->next=NULL;
		if(sum<=capacityOfEachTruck){
			boxWeight->next=temp;
			temp=boxWeight;
			continue;
		}
		numberOfTrucks++;
		struct weight* temp2=temp;
		while(temp!=NULL){
			printf("%d ",temp->weightValue);
			temp=temp->next;
			free(temp2);
			temp2=temp;
		}
		printf("\n");
		sum=*(weightOfBox+i);
		temp=boxWeight;
	}
	if(temp!=NULL)
		numberOfTrucks++;
	struct weight* temp2=temp;
	while(temp!=NULL){
		printf("%d ",temp->weightValue);
		temp=temp->next;
		free(temp2);
		temp2=temp;
	}
	printf("\napproximate number of trucks = %d\n",numberOfTrucks);

}

void optimalBinPackingSolution(int numberOfBoxes, int* weightOfBox, int capacityOfEachTruck){
	printf("optimal solution starts here\n");
	int i,j,numberOfTrucks=0,numOfDeletableWeights;
	while(numberOfBoxes>0){
		numOfDeletableWeights=0; 
		numberOfTrucks++;
		struct sumOfWeights* L0= malloc(sizeof(struct sumOfWeights));
		L0->value=0;
		L0->head=NULL;
		L0->next=NULL;
		for(i=0;i<numberOfBoxes;i++){
			struct sumOfWeights* l0;
			l0=L0;
			struct sumOfWeights* L1=malloc(sizeof(struct sumOfWeights));
			L1->value=L0->value + *(weightOfBox+i);
			struct weight* boxWeight1 = malloc(sizeof(struct weight));
			boxWeight1->weightValue = *(weightOfBox+i);
			boxWeight1->next=L0->head;
			L1->head=boxWeight1;
			L1->next=NULL;
			L0=L0->next;
			struct sumOfWeights* l1=L1;
			while(L0!=NULL){	
				struct sumOfWeights* nextL = malloc(sizeof(struct sumOfWeights));
				nextL->value=L0->value +  *(weightOfBox+i);
				struct weight* boxWeight = malloc(sizeof(struct weight));
				boxWeight->weightValue = *(weightOfBox+i);
				boxWeight->next=L0->head;
				nextL->head=boxWeight;
				nextL->next=NULL;
				L1->next=nextL;
				L1=nextL;
				L0=L0->next;
			};
			L0=mergeLists(l0,l1);
			L0=deleteBigNodes(L0,capacityOfEachTruck);
		}
		struct sumOfWeights* temp=L0->next;
		while(temp!=NULL){
			free(L0);
			L0=temp;
			temp=temp->next;
		}
		struct weight* w=L0->head;
		while(w!=NULL){
			printf("%d ",w->weightValue);
			for(i=0;i<numberOfBoxes;i++){
				if(w->weightValue== *(weightOfBox+i)){
					numOfDeletableWeights++;
					for(j=i;j<numberOfBoxes-1;j++){
						 *(weightOfBox+j) = *(weightOfBox+j+1);
					}
					break;
				}
			}
			w=w->next;
		}
		printf("\n");
		numberOfBoxes=numberOfBoxes-numOfDeletableWeights;
		free(L0);
		//L0=NULL;
	}
	printf("Ideal Number of trucks = %d\n",numberOfTrucks);

}
struct sumOfWeights* deleteBigNodes(struct sumOfWeights* head, int capacityOfEachTruck){
	if(head==NULL||head->value>capacityOfEachTruck){
		return NULL;
	} 
	struct sumOfWeights* L0=head;
	struct sumOfWeights* nextL0=L0->next;
	while(nextL0!=NULL&&nextL0->value<=capacityOfEachTruck){
		L0=L0->next;
		nextL0=nextL0->next;
	}
	L0->next=NULL;
	return head;
}

struct sumOfWeights* mergeLists(struct sumOfWeights* list1,struct sumOfWeights* list2){
	if(list1==NULL){
		return list2;
	} else if(list2==NULL){
		return list1;
	}
	struct sumOfWeights* mergedList;
	if(list1!=NULL && list2!=NULL){
		if(list1->value<list2->value){
			mergedList=list1;
			list1=list1->next;
		}else{
			mergedList=list2;
			list2=list2->next;
		}
	}
	struct sumOfWeights* tail=mergedList;
	while(list1!=NULL && list2!=NULL){
		if(list1->value<list2->value){
			tail->next=list1;
			tail=list1;
			list1=list1->next;
		}else{	
			tail->next=list2;
			tail=list2;
			list2=list2->next;
		}
	}
	if(list1==NULL){
		tail->next=list2;
	} else if(list2==NULL){
		tail->next=list1;
	}
	return mergedList;
}
