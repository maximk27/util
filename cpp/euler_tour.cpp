#include <bits/stdc++.h>
using namespace std;

struct EulerRange {
    int t_in;
    int t_out;
};
vector<EulerRange> EulerTour(vector<vector<int>> &adjlist, int start) {
    int n = adjlist.size();
    vector<EulerRange> ranges(n);

    int time = -1;
    auto Dfs = [&](auto &&self, int prev, int curr) -> void {
        int t_in = ++time;
        for (int next : adjlist[curr]) {
            if (next != prev)
                self(self, curr, next);
        }
        int t_out = time;
        ranges[curr] = EulerRange{
            t_in,
            t_out,
        };
    };
    Dfs(Dfs, -1, start);

    return ranges;
}
