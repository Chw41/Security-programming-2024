
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
        // 檢查除法運算
        // 除數 si2 為零，進行除法運算會導致程式崩潰 (除以零是未定義的行為)
        // 如果被除數 si1 為 INT_MIN，且除數 si2 為 -1，則除法結果會超出整數範圍(無法表示為 32 位有號整數)，導致overflow
        if (si2 == 0 || (si1 == INT_MIN && si2 == -1)){
                    printf("Error detected!\n");
                }
                else{
                    result = si1 / si2; 
                    printf("%d\n",result);
                }
    	S+=1;
    }

    return 0;
}

