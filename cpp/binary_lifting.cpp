#include <bits/stdc++.h>
using namespace std;

// ========================================================================
// BINARY LIFTING
// ========================================================================
vector<vector<int>> Get(vector<int> &ps, int l) {
    // where l = log2(max_d)
    int64_t n = ps.size();
    vector<vector<int>> parents(n, vector<int>(l, 0));
    for (int node = 0; node < n; node++) {
        parents[node][0] = ps[node];
    }

    for (int d = 1; d < l; d++) {
        for (int i = 0; i < n; i++) {
            parents[i][d] = parents[parents[i][d - 1]][d - 1];
        }
    }

    return parents;
}

int jump(vector<vector<int>> &parents, int x, int k, int l) {
    for (int i = 0; i < l; i++) {
        if (k & (1 << i)) {
            x = parents[x][i];
        }
    }
    return x;
}

struct Query {
    int x, k;
};
