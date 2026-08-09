#include <iostream>
#include <vector>

using namespace std;

class BIT {
    vector<int64_t> tree;

private:
    int GetLSB(int val) {
        return val & (-val);
    }

public:
    BIT(int n) : tree(n + 1, 0) {
    }

    // [0, k]
    int64_t Sum(int k) {
        k++;
        int64_t sum = 0;
        while (k >= 1) {
            sum += tree[k];
            k -= GetLSB(k);
        }
        return sum;
    }

    // [l, r]
    int64_t Sum(int l, int r) {
        return Sum(r) - Sum(l - 1);
    }

    void Add(int k, int64_t d) {
        k++;
        while (k < tree.size()) {
            tree[k] += d;
            k += GetLSB(k);
        }
    }
};
