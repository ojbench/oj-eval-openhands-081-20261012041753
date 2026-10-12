#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int MAXN = 3005;

int adj[MAXN][4];  // Each node has at most 3 neighbors
int deg[MAXN];
bool visited[MAXN];
int parent[MAXN];
int tempCap[MAXN][MAXN];

// Find one augmenting path using BFS
bool findPath(int s, int t, int n) {
    memset(parent, -1, sizeof(parent));
    memset(visited, false, sizeof(visited));
    
    queue<int> q;
    q.push(s);
    visited[s] = true;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int i = 0; i < deg[u]; i++) {
            int v = adj[u][i];
            if (!visited[v] && tempCap[u][v] > 0) {
                parent[v] = u;
                visited[v] = true;
                if (v == t) return true;
                q.push(v);
            }
        }
    }
    
    return false;
}

// Calculate max flow between s and t
int maxFlow(int s, int t, int n) {
    // Reset capacities - use memset for speed
    memset(tempCap, 0, sizeof(tempCap));
    for (int u = 1; u <= n; u++) {
        for (int i = 0; i < deg[u]; i++) {
            int v = adj[u][i];
            tempCap[u][v] = 1;
        }
    }
    
    int flow = 0;
    
    // Since max degree is 3, max flow is at most 3
    while (flow < 3 && findPath(s, t, n)) {
        // Update capacities along the path
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            tempCap[u][v]--;
            tempCap[v][u]++;
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
            totalSum += maxFlow(a, b, n);
        }
    }
    
    cout << totalSum << endl;
    
    return 0;
}