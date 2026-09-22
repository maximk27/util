import sys
from argparse import ArgumentParser
from sortedcontainers import SortedDict

if __name__ == "__main__":
    parser = ArgumentParser()
    parser.add_argument("text", help="input text", type=str)
    args = parser.parse_args()

    s = args.text

    charfreq = dict()
    for c in s:
        # NOTE: no case checking
        c = c.lower()
        charfreq[c] = charfreq.get(c, 0) + 1

    # freq -> [keys...]
    items = SortedDict(int)
    for c, freq in charfreq.items():
        items[freq] = items.get(freq, [])
        items[freq].append(c)

    for freq, keys in reversed(items.items()):
        print(f"freq={freq}, keys={keys}")

    print(
        f"total_length={len(s)}, unique_chars={len(charfreq)}, unique_sizes={len(items)}"
    )
