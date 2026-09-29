#include <numeric>
#include <vector>

using namespace std;

class DSU {
public:
    vector<int> rep;

    DSU(int n) {
        rep.resize(n);
        iota(begin(rep), end(rep), 0);
    }

    int find(int a) {
        if (rep[a] == a)
            return a;
        return rep[a] = find(rep[a]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b)
            return false;
        rep[b] = a;
        return true;
    }
};
