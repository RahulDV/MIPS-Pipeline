#include<Stdio.h>
struct sumOfWeights{
	int value;
	struct queue* head;
	struct list* next;
}
struct queue{
	int weight;
	struct queue* head;
}
int main(){
	int numberOfBoxes,i;
	scanf("%d",&numberOfBoxes);
	int weightOfBox[numberOfBoxes];
	int capacityOfEachTruck;
	scanf("%d",&capacityOfEachTruck);
	for(i=0;i<numberOfBoxes;i++){
		scanf("%d",&weightOfBox[i];
	}
	struct sumOfWeights L0;
	L0.value=0;
	L0.head=NULL;
	L0.next=NULL;
	larray[0]=L0;
		struct sumOfWeights larray[2];

	for(i=0;i<numberOfBoxes;i++){
		
	} 
}

struct sumOfWeights* mergeLists(struct sumOfWeights* list1,struct sumOfWeights* list2){
	struct sumOfWeights mergedList;
	struct sumOfWeights* tail=&mergedList;
	if(list1!=NULL && list2!=NULL){
		if(list1->value<list2->value){
			mergedList.value=list1->value;
			list1=list1->next;
		}else{
			mergedList.value=list2->value;
			list2=list2->next;
		}
		mergedList.next=NULL;
	}
	while(list1!=NULL && list2!=NULL){
		if(list1->value<list2->value){
			tail->next=list1;
			list1=list1->next;
		}else{	
			tail->next=list2;
			list2=list2->next;
		}
		tail=tail->next;
	}
	if(list1==NULL){
		tail->next=list2;
	} else if(list2==NULL){
		tail->next=list1;
	}
	return &mergedList;
}
