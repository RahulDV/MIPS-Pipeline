#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

    int length,key,i=0;
    scanf("%d",&length);
    char enteredString[length];
    unsigned char temp;
    scanf("%s",enteredString);
    scanf("%d",&key);
    key=key%26;
    while(enteredString[i]!='\0'){
        if(enteredString[i]>=65&&enteredString[i]<=90){
            temp=enteredString[i]+key;
	    if(temp>90)
		temp=temp%91+65;	
            enteredString[i]=temp;
        }else if(enteredString[i]>=97&&enteredString[i]<=122){
            temp=enteredString[i]+key;
	    if(temp>122)
		temp=temp%123+97;	
            enteredString[i]=temp;
        }
        i++;
    }
    printf("%s",enteredString);
    return 0;
}

