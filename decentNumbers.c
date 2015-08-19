#include<stdio.h>
#include<stdlib.h>
typedef struct maxFactor{
	int x;
	int y;


} maxFactor;
int main(){
	int i,T,x,y;
	scanf("%d",&T);
	int N[T];
	for(i=0;i<T;i++){
		scanf("%d",&N[i]);
	}
	for(i=0;i<T;i++){
		maxFactor* mf=malloc(sizeof(maxFactor));
		int temp;
		mf->x=mf->y=0;
		for(x=0;x*3<=N[i];x++){
			for(y=0;y*5<=N[i];y++){
				temp = 3*x+5*y;
				if(temp==N[i]){
					mf->x=x;		
					mf->y=y;
					break;
				}
			}
		}
		mf->x=mf->x*3;
		mf->y=mf->y*5;
		if(mf->x==0&&mf->y==0){
			printf("-1\n");
			continue;
		}
		while(mf->x>0){
			printf("5");
			mf->x=mf->x-1;
		}
		while(mf->y>0){
			printf("3");
			mf->y=mf->y-1;
		}
		printf("\n");
		free(mf);
	}
}
