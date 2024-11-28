#include <iostream>  
#include <vector>  
#include <algorithm>  
#include <cstdio>

using namespace std;  
  
bool can_place_shops(const vector<pair<int, int>>& regions, int N, int minDist) {  
    int count = 1;  
    int lastPos = regions[0].first;  
    for (const auto& region : regions) {  
        for (int i = max(region.first, lastPos + minDist); i <= region.second; i += minDist) {  
            count++;  
            lastPos = i;  
            if (count == N) {  
                return true;  
            }  
        }  
    }  
    return false;  
}  
  
int binary_search(const vector<pair<int, int>>& regions, int N){  
    int left = 1, right = regions.back().second - regions.front().first, result = 0;  
  
    while(left <= right){  
        int mid = (left + right) / 2;  
        if(can_place_shops(regions, N, mid)){  
            result = mid;  
            left = mid + 1;  
        }  
        else{  
            right = mid - 1;  
        }  
  
    }  
    return result;  
}  
  
int main() {   
    int N, M;  
    scanf("%d %d", &N, &M);  
      
    vector<pair<int, int>> regions(M);  
    for (int i = 0; i < M; ++i) {  
        scanf("%d %d", &regions[i].first, &regions[i].second);  
    }  
      
    sort(regions.begin(), regions.end());  
      
    printf("%d\n", binary_search(regions, N));  
      
    return 0;  
}
