from random import randint

n = randint(100000, 1000000)
m = randint(1, min(n * (n - 1) / 2, 1000000))
print(n, m)
print(n, m)
edges = set([])
for edge in range(0, m):
    u = randint(1, n)
    v = randint(u + 1, n + 1)
    while u * n + v in edges:
        u = randint(1, n)
        v = randint(u + 1, n + 1)
    edges.add(u * n + v)
    if randint(0, 1) == 1:
        print(u, v)
    else:
        print(v, u)
