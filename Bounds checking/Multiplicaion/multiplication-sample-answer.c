
#include <stdio.h>
#include <limits.h>


int main()
{
    int S=0, N=0;
    scanf("%d", &N);
    while(S<N){
        int si1=0,si2=0,result=0;
        scanf("%d %d", &si1, &si2);
        // 檢查乘法運算
        // 1. si1 和 si2 都是正數，且 si1 乘以 si2 的結果超過了 INT_MAX，導致overflow
        // 2. si1 和 si2 都是負數，且 si1 乘以 si2 的結果會低於 INT_MIN，導致overflow
        // 3. si1 是正數且 si2 是負數，但 si2 乘以 si1 的結果會低於 INT_MIN，導致overflow
        // 4. si1 是負數且 si2 是正數，但 si1 乘以 si2 的結果會低於 INT_MIN，導致overflow
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

