#include<stdio.h>
#include<stdlib.h>
typedef struct list{
	int value;
	struct list* next;
} list;
int main(){
	int t,i,j;
	scanf("%d",&t);
	int n[t];
	for(i=0;i<t;i++){
		scanf("%d",&n[i]);		
	}
	for(i=0;i<t;i++){
		j=1;
		list* first = malloc(sizeof(list));
		first->value=n[i];
		first->next=NULL;
		list* temp;
		while(n[i]-j>j){
			temp = malloc(sizeof(list));
			temp->value=j;
			temp->next=first;
			first=temp;
			temp = malloc(sizeof(list));
			temp->value=n[i]-j;
			temp->next=first;
			first=temp;	
			j++;
		}if(n[i]-j==j){
			temp = malloc(sizeof(list));
			temp->value=j;
			temp->next=first;
			first=temp;
		}
		while(first!=NULL){
			printf("%d ",first->value);
			first=first->next;
			free(temp);
			temp=first;
		}
		printf("\n");
	}
	return 0;
}

