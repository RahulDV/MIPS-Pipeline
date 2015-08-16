#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int i,hours24,hours12;
    char time[10];
    scanf("%[^\n]s",time);
    hours12 =  (time[0]-'0')*10+(time[1]-'0');

    if(time[8]=='P'&&hours12!=12){
        hours24 = hours12+12;
        time[0] = '0' + (int)floor(hours24/10);
        time[1] = '0' + hours24%10;
    } else if(time[8]=='A'&&hours12==12){
        time[0] = '0';
        time[1] = '0';
    }
    for(i=0;i<8;i++){
       printf("%c",time[i]); 
    }
    
    return 0;
}

