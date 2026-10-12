#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int MAXN = 3005;

int adj[MAXN][4];  // Each node has at most 3 neighbors + sentinel
int deg[MAXN];
int parent[MAXN];
bool visited[MAXN];
int cap[MAXN][MAXN];

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
        
        for (int i = 0; i < deg[u]; i++) {
            int v = adj[u][i];
            if (!visited[v] && cap[u][v] > 0) {
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
    // Reset capacities
    memset(cap, 0, sizeof(cap));
    for (int u = 1; u <= n; u++) {
        for (int i = 0; i < deg[u]; i++) {
            int v = adj[u][i];
            cap[u][v] = 1;
        }
    }
    
    int flow = 0;
    
    while (bfs(s, t, n)) {
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            cap[u][v]--;
            cap[v][u]++;
        }
        flow++;
    }
    
    return flow;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    // Initialize
    memset(deg, 0, sizeof(deg));
    memset(adj, -1, sizeof(adj));
    
    // Read edges
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u][deg[u]++] = v;
        adj[v][deg[v]++] = u;
    }
    
    long long totalSum = 0;
    
    // Calculate max flow for all pairs (a, b) where a < b
    for (int a = 1; a <= n; a++) {
        for (int b = a + 1; b <= n; b++) {
            int flow = maxFlow(a, b, n);
            totalSum += flow;
        }
    }
    
    cout << totalSum << endl;
    
    return 0;
}