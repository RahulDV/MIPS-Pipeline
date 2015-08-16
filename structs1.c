#include<stdio.h>
int main(){
	struct book{
		char name;
		float price;
		int pages;
	};
	struct book b1={'r',155.50,200};
	printf("%c\t%f\t%d\n",b1.name,b1.price,b1.pages);
	printf("%p\t%p\t%p\n",&b1.name,&b1.price,&b1.pages);
	printf("b1 = %p\t b1+1 = %p\n",&b1,&b1+1);
	return 0;

}
