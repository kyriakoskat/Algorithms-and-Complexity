#include <cstdio>
#include <algorithm>
#include <climits>

const int MAX_N = 2500;
const int MAX_K = 700;

int A_matrix[2501][2501];
int prefix_sum[2501][2501];
int cost_matrix[2501][2501];
int dp_matrix[701][2501];

int main(){
    int N, K;
    scanf("%d %d", &N, &K);

    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            A_matrix[i][j] = 0;
        }
    }

    for(int i = 1; i < N; i++){
        for(int j = i+1; j <= N; j++){
            int value;
            scanf("%d", &value);
            A_matrix[i][j] = value;
            A_matrix[j][i] = value; 
        }
    }

    for(int j = 1; j <= N; j++){
        prefix_sum[0][j] = 0;
        for(int i = 1; i <= N; i++){
            prefix_sum[i][j] = prefix_sum[i-1][j] + A_matrix[i][j];
        }
    }

    for(int l = 1; l <= N; l++){
        for(int r = l; r <= N; r++){
            if(l == r){
                cost_matrix[l][r] = 0;
            }
            else{
                cost_matrix[l][r] = cost_matrix[l][r-1] + (prefix_sum[r-1][r] - prefix_sum[l-1][r]);
            }
        }
    }

    
    for(int k = 0; k <= K; k++){
        for(int n = 0; n <= N; n++){
            dp_matrix[k][n] = INT_MAX; 
        }
    }

    dp_matrix[0][0] = 0; 

    for(int k = 1; k <= K; k++){
        for(int n = 1; n <= N; n++){
            if(k > n){
                dp_matrix[k][n] = INT_MAX; 
                continue;
            }
            for(int m = k-1; m < n; m++){
                if(dp_matrix[k-1][m] == INT_MAX){
                    continue; 
                }
                int new_cost = dp_matrix[k-1][m] + cost_matrix[m+1][n];
                if(new_cost < dp_matrix[k][n]){
                    dp_matrix[k][n] = new_cost;
                }
            }
        }
    }

    printf("%d\n", dp_matrix[K][N]);

    return 0;
}
