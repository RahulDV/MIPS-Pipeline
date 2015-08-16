#include<stdio.h>
void display(int *n);
int main()
{
	int i;
	int marks[]={55,65,75,56,78,78,90};
	for(i=0;i<7;i++){
		display(&marks[i]);
	}
	printf("%p %p %d\n",marks+4,&marks+2,*marks);
	return 0;
}
void display(int *n)
{
	printf("%p %p %d\n",&n,n,*n);
}
