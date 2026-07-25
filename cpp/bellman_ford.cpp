#include <bits/stdc++.h>
#include <cassert>
using namespace std;

constexpr const int64_t INF = int64_t(1e13);

struct Edge {
    int a, b;
    int64_t x;
};

// Bellman Ford
optional<vector<int64_t>> BellmanFord(const vector<Edge> &edges) {
    int n = edges.size();
    bool pos_cycle = false;
    vector<int64_t> min_dist(n, 0);
    for (int i = 0; i < n; i++) {
        // try improve n times
        bool improve = false;
        for (auto [a, b, x] : edges) {
            int64_t cand = min_dist[a] + x;
            int64_t prev = min_dist[b];
            if (prev < cand) {
                min_dist[b] = cand;
                improve = true;
            }
        }
        if (!improve) {
            break;
        }
        // improved more than n-1 times
        // pigeonhole exists cycle
        if (i == n - 1) {
            pos_cycle = true;
            break;
        }
    }
    if (pos_cycle)
        return std::nullopt;
    return min_dist;
}
