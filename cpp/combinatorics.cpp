#include <bits/stdc++.h>
#include <cassert>

using namespace std;

// ========================================================================
// SINGLE USE
// ========================================================================
int64_t Pow(int64_t base, int64_t exp, int64_t mod) {
    // a^b = (a^2)^(b/2)
    base %= mod;
    exp %= mod;
    int64_t res = 1;
    while (exp > 0) {
        if (exp % 2 == 0) {
            base = (base * base) % mod;
            exp /= 2;
        } else {
            res = (res * base) % mod;
            exp--;
        }
    }
    return res;
}

int64_t ModInv(int64_t val, int64_t mod) {
    // (b^e = b) mod m
    return Pow(val, mod - 2, mod);
}

int64_t NCR(int64_t n, int64_t r) {
    // n! / r!(n-r)!
    if (r > n) {
        return 0;
    }
    int64_t res = 1;
    for (int64_t i = 1; i <= r; i++) {
        res *= (n - i + 1);
        res /= i;
    }
    return res;
}

int64_t NCR(int64_t n, int64_t r, int64_t mod) {
    if (r > n) {
        return 0;
    }
    int64_t num = 1;
    int64_t denom = 1;
    for (int64_t i = 1; i <= r; i++) {
        num = (num * (n - i + 1)) % mod;
        denom = (denom * i) % mod;
    }

    return (num * ModInv(denom, mod)) % mod;
}

int64_t StarsAndBars(int64_t n, int64_t k) {
    // n + k - 1 supply
    // k - 1 borders to create the k groupings
    // (n + k - 1) choose (k - 1)
    return NCR(n + k - 1, k - 1);
}

// ========================================================================
// PRECOMPUTE MULTI USE
// ========================================================================
struct Combinatorics {
    int64_t mod;
    vector<int64_t> fact;
    vector<int64_t> inv_fact;

    Combinatorics(int64_t n, int64_t mod) {
        fact.resize(n + 1);
        inv_fact.resize(n + 1);

        fact[0] = 1;
        for (int64_t i = 1; i <= n; i++) {
            fact[i] = (fact[i - 1] * i) % mod;
        }

        inv_fact[n] = ::ModInv(fact[n], mod);
        for (int64_t i = n - 1; i >= 0; i--) {
            // (i+1)! = (i+1) * i!
            // 1/i! = (i+1)/(i+1)!
            inv_fact[i] = ((i + 1) * inv_fact[i + 1]) % mod;
        }
    }

    int64_t NCR(int64_t n, int64_t r) {
        // n! / r!(n - r)!
        return ((fact[n] * inv_fact[r]) % mod * inv_fact[n - r]) % mod;
    }
};
