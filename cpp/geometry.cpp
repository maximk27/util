#include <bits/stdc++.h>
using namespace std;

struct Point {
    int64_t x, y;
    Point operator-(Point b) {
        return Point{x - b.x, y - b.y};
    }
    int64_t Cross(Point b) {
        return x * b.y - y * b.x;
    }
};
int Orient(Point p1, Point p2, Point test) {
    Point line = p2 - p1;
    Point t_line = test - p1;
    int64_t res = line.Cross(t_line);
    if (res < 0)
        return -1;
    if (res > 0)
        return 1;
    return 0;
}

bool InsideSegment(Point p1, Point p2, Point test) {
    auto lx = min(p1.x, p2.x), rx = max(p1.x, p2.x);
    auto ly = min(p1.y, p2.y), ry = max(p1.y, p2.y);
    return (lx <= test.x && test.x <= rx) && (ly <= test.y && test.y <= ry);
}

bool Crosses(Point p1, Point p2, Point p3, Point p4) {
    array<Point, 4> p = {p1, p2, p3, p4};
    auto GetOthers = [&](int idx) -> pair<int, int> {
        int base = (idx + 2) % 4;
        base -= base % 2;
        return {base, base + 1};
    };

    array<int, 4> orients;
    for (int i = 0; i < 4; i++) {
        auto [j, k] = GetOthers(i);
        orients[i] = Orient(p[j], p[k], p[i]);
        if (orients[i] == 0 && InsideSegment(p[j], p[k], p[i])) {
            return true;
        }
    }
    return (orients[0] != orients[1]) && (orients[2] != orients[3]);
}
