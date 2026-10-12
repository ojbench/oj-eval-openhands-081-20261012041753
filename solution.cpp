#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 3005;
const int MAXM = 4505;

vector<int> adj[MAXN];
int capacity[MAXN][MAXN];
int parent[MAXN];
bool visited[MAXN];

int bfs(int s, int t, int n) {
    memset(parent, -1, sizeof(parent));
    memset(visited, false, sizeof(visited));
    
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v : adj[u]) {
            if (!visited[v] && capacity[u][v] > 0) {
                parent[v] = u;
                visited[v] = true;
                q.push(v);
                
                if (v == t) {
                    return 1;
                }
            }
        }
    }
    
    return 0;
}

int maxFlow(int s, int t, int n) {
    int flow = 0;
    
    while (bfs(s, t, n)) {
        int pathFlow = 1;
        
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            capacity[u][v] -= pathFlow;
            capacity[v][u] += pathFlow;
        }
        
        flow += pathFlow;
    }
    
    return flow;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    // Initialize adjacency list and capacity matrix
    for (int i = 1; i <= n; i++) {
        adj[i].clear();
    }
    memset(capacity, 0, sizeof(capacity));
    
    // Read edges
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        capacity[u][v] = 1;
        capacity[v][u] = 1;
    }
    
    long long totalSum = 0;
    
    // Calculate max flow for all pairs (a, b) where a < b
    for (int a = 1; a <= n; a++) {
        for (int b = a + 1; b <= n; b++) {
            // Reset capacities for this pair
            for (int u = 1; u <= n; u++) {
                for (int v : adj[u]) {
                    if (u < v) {
                        capacity[u][v] = 1;
                        capacity[v][u] = 1;
                    }
                }
            }
            
            int flow = maxFlow(a, b, n);
            totalSum += flow;
        }
    }
    
    cout << totalSum << endl;
    
    return 0;
}