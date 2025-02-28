#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

typedef long long ll;
const ll INF = 1000000000000000000LL; 
const int INF_INT = 1000000000;        

const int MAX_N = 1000;    
const int MAX_M = 10000;   

struct Edge {
    int to;
    int cost;
    int next; 
};

Edge edges[MAX_M + 1];
int head[MAX_N + 1];  
int edgeCount = 0;

void addEdge(int u, int v, int cost) {
    edgeCount++;
    edges[edgeCount].to = v;
    edges[edgeCount].cost = cost;
    edges[edgeCount].next = head[u];
    head[u] = edgeCount;
}

struct State {
    int node;   
    int used;    
    ll time;     
};

struct StateComparator {
    bool operator()(const State &a, const State &b) const {
        if(a.used != b.used)
            return a.used > b.used;
        return a.time > b.time;
    }
};

int main(){
    int N, M, s, t;
    ll B;
    scanf("%d %d %d %d %lld", &N, &M, &s, &t, &B);
    
    for (int i = 1; i <= N; i++) {
        head[i] = -1;
    }
    
    for (int i = 0; i < M; i++){
        int u, v, l;
        scanf("%d %d %d", &u, &v, &l);
        addEdge(u, v, l);
    }
    
    int minEdges[MAX_N + 1];
    for (int i = 1; i <= N; i++){
        minEdges[i] = INF_INT;
    }
    minEdges[s] = 0;
    
    queue<int> q;
    q.push(s);
    
    while(!q.empty()){
        int cur = q.front();
        q.pop();
        for (int i = head[cur]; i != -1; i = edges[i].next){
            int nxt = edges[i].to;
            if(minEdges[nxt] > minEdges[cur] + 1){
                minEdges[nxt] = minEdges[cur] + 1;
                q.push(nxt);
            }
        }
    }
    
    if(minEdges[t] == INF_INT){
        printf("-1\n");
        return 0;
    }
    int maxAllowed = minEdges[t]; 
    
    static ll dp[MAX_N + 1][MAX_N + 1];
    for (int i = 1; i <= N; i++){
        for (int k = 0; k <= MAX_N; k++){
            dp[i][k] = INF;
        }
    }
    dp[s][0] = 0;
    
    priority_queue<State, vector<State>, StateComparator> pq;
    pq.push({s, 0, 0});
    
    while(!pq.empty()){
        State cur = pq.top();
        pq.pop();
        int u = cur.node, used = cur.used;
        ll curTime = cur.time;
        
        if(curTime > B)
            continue;
        if(curTime != dp[u][used])
            continue;
        
        if(u == t){
            printf("%d\n", used);
            return 0;
        }
        
        for (int i = head[u]; i != -1; i = edges[i].next){
            int v = edges[i].to;
            int l = edges[i].cost;
            
            ll newTime = curTime + l;
            if(newTime < dp[v][used] && newTime <= B){
                dp[v][used] = newTime;
                pq.push({v, used, newTime});
            }
            
            if(used < maxAllowed){
                if(curTime < dp[v][used + 1]){
                    dp[v][used + 1] = curTime;
                    pq.push({v, used + 1, curTime});
                }
            }
        }
    }
    
    printf("-1\n");
    return 0;
}
