#include <bits/stdc++.h>
using namespace std;

// 0 indexed scc
// { num_scc, scc_mapping }
pair<int, vector<int>> GetSCC(vector<vector<int>> &adjlist) {
    // tarjans algorithm
    int n = adjlist.size();
    int components_size = 0;
    int timer = 0;
    vector<int> components(n, 0);
    vector<int> tins(n, 0);
    vector<int> lows(n);
    stack<int> st;
    auto Dfs = [&](auto &&self, int v) -> void {
        tins[v] = lows[v] = ++timer;
        st.push(v);
        for (int w : adjlist[v]) {
            if (!tins[w]) {
                self(self, w);
                lows[v] = min(lows[v], lows[w]);
            } else if (!components[w]) {
                lows[v] = min(lows[v], tins[w]);
            }
        }
        if (lows[v] == tins[v]) {
            int id = ++components_size;
            while (true) {
                int curr = st.top();
                st.pop();
                components[curr] = id;
                if (curr == v)
                    break;
            }
        }
    };

    for (int node = 0; node < n; node++) {
        if (!components[node]) {
            Dfs(Dfs, node);
        }
    }
    for (int i = 0; i < n; i++) {
        components[i] = components_size - components[i];
    }
    return {components_size, components};
}

// { adjlist, coins }
pair<vector<vector<int>>, vector<int64_t>>
Compress(vector<vector<int>> &adjlist, vector<int64_t> &coins) {
    auto [c_size, components] = GetSCC(adjlist);
    vector<vector<int>> n_adjlist(c_size);
    vector<int64_t> n_coins(c_size, 0);

    for (int i = 0; i < adjlist.size(); i++) {
        int c = components[i];
        for (int next : adjlist[i]) {
            int n_c = components[next];
            if (n_c != c) {
                n_adjlist[c].push_back(n_c);
            }
        }
        n_coins[c] += coins[i];
    }
    for (int i = 0; i < c_size; i++) {
        auto &v = n_adjlist[i];
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
    }

    return {n_adjlist, n_coins};
}
