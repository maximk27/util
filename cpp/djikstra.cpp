#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int next;
    int64_t dist;
    bool operator<(Edge e) const {
        return dist > e.dist;
    }
};

constexpr const int64_t INF = int64_t(1e14);

vector<int64_t> Djikstra(vector<vector<Edge>> &adjlist, int source) {
    int64_t n = adjlist.size();
    priority_queue<Edge> pq;
    pq.push(Edge{source, 0});
    vector<int64_t> min_dist(n, INF);
    while (!pq.empty()) {
        auto [u, u_dist] = pq.top();
        pq.pop();
        if (min_dist[u] != INF) {
            continue;
        }
        min_dist[u] = u_dist;
        for (auto [v, dist] : adjlist[u]) {
            int64_t v_dist = u_dist + dist;
            if (min_dist[v] != INF)
                continue;
            pq.push(Edge{v, v_dist});
        }
    }
    return min_dist;
}
