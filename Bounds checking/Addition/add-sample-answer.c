
#include <stdio.h>
#include <limits.h>


int main()
{
    int S=0, N=0;
    scanf("%d", &N);
    while(S<N){
        int si1=0,si2=0,result=0;
        scanf("%d %d", &si1, &si2);
        /* 
        si1+si2 > MAX or si1+si2 < min
        = si1 > MAX-si2 or si1 < min-si2
        檢查加法運算:
         如果 si1 是正數且 si2 與 INT_MAX - si1 的總和超過了 INT_MAX，會導致overflow
         如果 si1 是負數且 si2 與 INT_MIN - si1 的總和低於 INT_MIN，也會導致overflow
        */
        if ((si1 > 0 && si2 > INT_MAX - si1) || (si1 < 0 && si2 < INT_MIN - si1)){
                    printf("Error detected!\n");
                }
                else{
                    result = si1 + si2; 
                    printf("%d\n",result);
                }
    	S+=1;
    }

    return 0;
}

