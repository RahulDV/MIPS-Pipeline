#include<stdio.h>
int main(){

	//This program tests the casting properties of pointers. Here character datatype pointer is cast to an integer datatype pointer. Hence when ever we perform pointer arithmatic on this pointer it behaves like an integer. For example the below program prints only r and l as for each pointer increment by one the address pointer moves 4 bytes.. Since each character takes 1 byte hence the address pointer points to 4 characters after 'r' including 'r' i.e 'l'.
	char name[15]="rahuldan";
	int i=0;
	char *ptr;
	int *intptr;
	ptr=name;
	intptr = (int *)ptr;
	while(*intptr!='\0'&&i<8){
		printf("%c",*intptr);
		intptr++;
		i++;
	}
	printf("\n");	
	return 0;
}
	
