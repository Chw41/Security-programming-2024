
#include <stdio.h>
#include <limits.h>


int main()
{
    int S=0, N=0;
    scanf("%d", &N);
    while(S<N){
        int si1=0,si2=0,result=0;
        scanf("%d %d", &si1, &si2);
        if ((si1 > 0 && si2 > 0 && si1 > INT_MAX / si2) || (si1 < 0 && si2 < 0 && si1 < INT_MIN / si2) || (si1 > 0 && si2 < 0 && si2 < INT_MIN / si1) || (si1 < 0 && si2 > 0 && si1 < INT_MIN / si2)){
                    printf("Error detected!\n");
                }
                else{
                    result = si1 * si2; 
                    printf("%d\n",result);
                }
    	S+=1;
    }

    return 0;
}

