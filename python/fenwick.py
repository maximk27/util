class FenwickTree:
    bit = []
    n = 0

    def __init__(self, n):
        self.n = n
        self.bit = [0] * n

    def sumr(self, r):
        ret = 0
        while r >= 0:
            ret += self.bit[r]
            r = (r & (r + 1)) - 1
        return ret

    def sum(self, l, r):
        return self.sum(r) - self.sum(l - 1)

    def add(self, idx, delta):
        while idx < self.n:
            self.bit[idx] += delta
            idx = idx | (idx + 1)
