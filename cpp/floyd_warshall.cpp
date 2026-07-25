#include <bits/stdc++.h>
using namespace std;

vector<vector<int64_t>> FloydWarshall(vector<vector<int64_t>> adjmat) {
    int n = adjmat.size();
    vector<vector<int64_t>> min_dist = std::move(adjmat);
    for (int i = 0; i < n; i++) {
        min_dist[i][i] = 0;
    }

    for (int mid = 0; mid < n; mid++) {
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                int64_t prev = min_dist[u][v];
                int64_t cand = min_dist[u][mid] + min_dist[mid][v];
                int64_t res = min(prev, cand);
                min_dist[u][v] = min_dist[v][u] = res;
            }
        }
    }
}
