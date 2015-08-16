#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
typedef struct list{
    long value;
    struct list* next;
} list;
int main() {

    int n,i,numOfDays=0,temp=1;
    scanf("%d",&n);
    list* first = malloc(sizeof(list));
    scanf("%ld",&(first->value));
    first->next=NULL;
    list* iterator = first;
    for(i=1;i<n;i++){
        list* temp = malloc(sizeof(list));
        scanf("%ld",&(temp->value));
        temp->next=NULL;
	iterator->next=temp;
        iterator=temp;
    }
    list* next=first->next;
    list* previous=first;
    while(temp){
        temp=0;
        while(next!=NULL){
            if(next->value>previous->value){
                temp=1;
                previous->next=next->next;
                next=next->next;
            	numOfDays++;
            }
            previous=previous->next;
            next=next->next;
        }
	
    }
    printf("%d\n",numOfDays);
    return 0;
}

