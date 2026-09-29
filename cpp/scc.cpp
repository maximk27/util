#include <bits/stdc++.h>
using namespace std;

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
    return {components_size, components};
}
