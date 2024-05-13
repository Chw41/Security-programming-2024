
#include <stdio.h>
#include <limits.h>


int main()
{
    int S=0, N=0;
    scanf("%d", &N);
    while(S<N){
        int si1=0,si2=0,result=0;
        scanf("%d %d", &si1, &si2);
        // 合法範圍: -2147483648 ~ 2147483647
        // 檢查減法運算
        // 如果 si2 是正數且 si1 與 INT_MIN + si2 的總和低於 INT_MIN，則減法將導致overflow
        // 如果 si2 是負數且 si1 與 INT_MAX + si2 的總和超過 INT_MAX，也導致溢出overflow
        if ((si2 > 0 && si1 < INT_MIN + si2) || (si2 < 0 && si1 > INT_MAX + si2)){
                    printf("Error detected!\n");
                }
                else{
                    result = si1 - si2; 
                    printf("%d\n",result);
                }
    	S+=1;
    }

    return 0;
}

