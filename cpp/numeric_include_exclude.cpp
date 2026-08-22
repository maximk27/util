#include <bits/stdc++.h>
using namespace std;

int64_t CountLTE(int64_t bound, vector<int> &nums) {
    int n = nums.size();
    int64_t total = 0;
    int m = 1 << n;
    for (int mask = 1; mask < m; mask++) {
        int64_t current_lcm = 1;
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                current_lcm = lcm(current_lcm, nums[i]);
            }
        }

        int64_t count = bound / current_lcm;
        if (__builtin_popcount(mask) % 2 == 1) {
            total += count;
        } else {
            total -= count;
        }
    }
    return total;
}
