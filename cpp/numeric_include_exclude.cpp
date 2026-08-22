#include <bits/stdc++.h>
using namespace std;

int64_t CountDivAtLeastOne(int64_t N, const vector<int64_t> &A) {
    if (N <= 0 || A.empty())
        return 0;

    int K = static_cast<int>(A.size());
    int64_t total = 0;
    int num_subsets = 1 << K;

    for (int mask = 1; mask < num_subsets; ++mask) {
        int64_t current_lcm = 1;
        for (int i = 0; i < K; ++i) {
            if (mask & (1 << i)) {
                current_lcm = lcm(current_lcm, A[i]);
            }
        }

        int64_t count = N / current_lcm;
        if (__builtin_popcount(mask) % 2 == 1) {
            total += count;
        } else {
            total -= count;
        }
    }

    return total;
}
