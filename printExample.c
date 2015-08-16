#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

    int size,i,scanValue;
    float countPositive=0.0,countNegitive=0.0,countZero=0.0;
    scanf("%d",&size);
    for(i=0;i<size;i++){
        scanf("%d",&scanValue);
        if(scanValue>0){
            countPositive++;
        } else if(scanValue<0){
            countNegitive++;
        } else {
            countZero++;
        }

    }
    printf("%f\n%f\n%f\n",countPositive/size,countNegitive/size,countZero/size);
    return 0;
}

