#include<stdio.h>
int main(){
	int i=3,*x;
	float j=1.5,*y;
	char k='c',*z;
	printf("%d\n",i);
	printf("%f\n",j);
	printf("%c\n",k);
	x=&i;
	y=&j;
	z=&k;
	printf("x,y,z = %p %p %p\n&x,&y,&z = %p %p %p\n",x,y,z,&x,&y,&z);
	printf("x+1,y+1,z+1 = %p %p %p\n&x+1,&y+1,&z+1 = %p %p %p\n",x+1,y+1,z+1,&x+1,&y+1,&z+1);
	return 0;

}

