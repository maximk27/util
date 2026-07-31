#include <bits/stdc++.h>

using namespace std;

enum State {
    Unvisited = 0,
    Visited = 1,
    Processed = 2,
};

// return true if exists cycle
bool dfs(vector<vector<int>> &adjlist, vector<State> &states, int u,
         vector<int> &ordering) {

    if (states[u] == Visited) {
        return true;
    }
    if (states[u] == Processed) {
        return false;
    }
    // else unvisited
    states[u] = Visited;

    for (int v : adjlist[u]) {
        if (dfs(adjlist, states, v, ordering)) {
            return true;
        }
    }
    ordering.push_back(u);
    states[u] = Processed;
    return false;
}

expected<vector<int>, string> TopologicalSort(vector<vector<int>> &adjlist) {
    int n = adjlist.size();
    vector<State> states(n);
    vector<int> ordering;
    for (int node = 0; node < n; node++) {
        if (dfs(adjlist, states, node, ordering)) {
            return unexpected("IMPOSSIBLE");
        }
    }
    reverse(begin(ordering), end(ordering));
    return ordering;
}
