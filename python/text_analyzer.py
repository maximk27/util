import sys

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print(f"usage: {sys.argv[0]} [string]")
        sys.exit(1)

    s = sys.argv[1]

    charfreq = dict()
    for c in s:
        # NOTE: no case checking
        c = c.lower()
        charfreq[c] = charfreq.get(c, 0) + 1

    items = [(freq, c) for c, freq in charfreq.items()]
    items.sort(reverse=True)

    for freq, c in items:
        print(f"k='{c}', freq={freq}")

    print(f"length={len(s)}, unique={len(items)}")
