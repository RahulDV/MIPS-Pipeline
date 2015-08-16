#include<stdio.h>
int setContain(unsigned long one,unsigned long *k,unsigned long nk);
int main(){
	unsigned long n,poss,nk,i,max=0,teamLength;
	scanf("%lu %lu",&n,&nk);
	unsigned long  k[nk];
	for(i=0;i<nk;i++){
		scanf("%lu",&k[i]);
	}
	for(i=0;i<nk;i++){
		teamLength=0;
		poss=k[i]-2;
		while(poss>=2){
			if(!setContain(poss,k,nk)){
				teamLength++;
			}
			poss=poss-2;
		}
		poss=k[i]+2;
		while(poss<=n){
			if(!setContain(poss,k,nk)){
				teamLength++;
			}
			poss=poss+2;
		}
		if(max<teamLength+nk)
			max=teamLength+nk;
	}
	printf("%lu\n",max);
	return 0;
}
int setContain(unsigned long one,unsigned long *k,unsigned long nk){
	unsigned long i;
	for(i=0;i<nk;i++){
		if(one==*k || one+1==*k || one-1==*k){
			return 1;
		}
		k=k+1;
	}
	return 0;
}
