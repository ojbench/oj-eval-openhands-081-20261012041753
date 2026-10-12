#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 3005;
const int MAXM = 4505;

vector<int> adj[MAXN];
vector<pair<int, int>> edges;
int parent[MAXN];
bool visited[MAXN];
int tempCap[MAXN][MAXN];

int bfs(int s, int t) {
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
            if (!visited[v] && tempCap[u][v] > 0) {
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

int maxFlow(int s, int t) {
    // Reset temporary capacities
    memset(tempCap, 0, sizeof(tempCap));
    for (auto& edge : edges) {
        int u = edge.first, v = edge.second;
        tempCap[u][v] = 1;
        tempCap[v][u] = 1;
    }
    
    int flow = 0;
    
    while (bfs(s, t)) {
        int pathFlow = 1;
        
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            tempCap[u][v] -= pathFlow;
            tempCap[v][u] += pathFlow;
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
    
    // Initialize adjacency list
    for (int i = 1; i <= n; i++) {
        adj[i].clear();
    }
    edges.clear();
    
    // Read edges
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        edges.push_back({u, v});
    }
    
    long long totalSum = 0;
    
    // Calculate max flow for all pairs (a, b) where a < b
    for (int a = 1; a <= n; a++) {
        for (int b = a + 1; b <= n; b++) {
            int flow = maxFlow(a, b);
            totalSum += flow;
        }
    }
    
    cout << totalSum << endl;
    
    return 0;
}