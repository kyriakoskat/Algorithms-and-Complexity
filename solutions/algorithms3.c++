#include <cstdio>
#include <algorithm>
using namespace std;

int main(){
    int N, K;
    
    scanf("%d %d", &N, &K);
    int* h = new int[N];
                                    
    for(int i = 0; i < N; ++i){
       scanf("%d", &h[i]);
    }
    
    int* dp = new int[N + 1](); 
    
    for(int i = 1; i <= N; ++i){
        int current_max = 0;
        for(int j = 1; j <= K && j <= i; ++j){
            current_max = max(current_max, h[i - j]);
            dp[i] = max(dp[i], dp[i - j] + current_max * j);
        }
    }
    
    printf("%d\n", dp[N]);    
    return 0;
}
