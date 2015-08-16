#include<stdio.h>
int main(){
	int i,emax,omax,n,nk,nek=0,nok=0;
	scanf("%d %d",&n,&nk);
	if(n%2==0){
		emax=omax=n/2;
	}else{
		emax=(n-1)/2;
		omax=(n+1)/2;
	}
	int k[nk];
	for(i=0;i<nk;i++){
		scanf("%d",&k[i]);
		if(k[i]%2==0 && (k[i]!=n || k[i]!=1)){
			nek++;
		}
		else if(k[i]!=n || k[i]!=1){
			nok++;
		}
	}
	if(nek>nok){
		printf("%d\n",emax-nok);	
	}else{
		printf("%d\n",omax-nek);
	}
	return 0;
	
}
