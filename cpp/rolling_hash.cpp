#include <bits/stdc++.h>
using namespace std;

class PrefixHash {
    static constexpr int P = 9973;
    static constexpr int M = 1e9 + 9;

    vector<int64_t> pref;
    vector<int64_t> pow;

public:
    PrefixHash(const string &s) {
        int n = s.size();
        pref.resize(n + 1, 0);
        pow.resize(n + 1, 1);

        for (int i = 0; i < n; i++) {
            pow[i + 1] = (pow[i] * P) % M;
            pref[i + 1] = (pref[i] * P + (s[i] - 'a' + 1)) % M;
        }
    }

    // [l, r] 0 indexed
    int64_t query(int l, int r) const {
        int64_t res = (pref[r + 1] - (pref[l] * pow[r - l + 1]) % M) % M;
        return (res + M) % M;
    }
};
