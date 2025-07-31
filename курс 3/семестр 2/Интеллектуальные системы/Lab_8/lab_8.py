import math


# Хелд–Карпа
def solve_tsp(dist):
    n = len(dist)
    N = 1 << n
    dp = [[math.inf] * n for _ in range(N)]
    parent = [[-1] * n for _ in range(N)]
    dp[1][0] = 0
    for mask in range(1, N):
        if not (mask & 1):
            continue
        for u in range(n):
            if not (mask & (1 << u)) or dp[mask][u] == math.inf:
                continue
            for v in range(n):
                if mask & (1 << v):
                    continue
                new_mask = mask | (1 << v)
                cost = dp[mask][u] + dist[u][v]
                if cost < dp[new_mask][v]:
                    dp[new_mask][v] = cost
                    parent[new_mask][v] = u
    full_mask = N - 1
    best_cost = math.inf
    last = 0
    for u in range(1, n):
        cost = dp[full_mask][u] + dist[u][0]
        if cost < best_cost:
            best_cost = cost
            last = u
    path_rev = [0]  # end at start
    mask = full_mask
    u = last
    while u != 0:
        path_rev.append(u)
        prev = parent[mask][u]
        mask ^= (1 << u)
        u = prev
    path_rev.append(0)
    path = list(reversed(path_rev))
    return best_cost, path


if __name__ == '__main__':
    INF = math.inf
    cities = [
        "Брест", "Орша", "Слоним", "Полоцк", "Барановичи",
        "Лида", "Мозырь", "Кобрин", "Бобруйск", "Гродно"
    ]
    dist_matrix = [
        [INF, 562, 198, 579, 214, 270, 415, 49, 482, 233],
        [562, INF, 408, 185, 358, 389, 334, 511, 195, 496],
        [198, 408, INF, 425, 60, 102, 355, 146, 328, 146],
        [579, 185, 425, INF, 375, 390, 457, 528, 317, 497],
        [214, 358, 60, 375, INF, 114, 315, 163, 277, 207],
        [270, 389, 102, 390, 114, INF, 465, 268, 328, 114],
        [415, 334, 355, 457, 315, 465, INF, 365, 140, 573],
        [49, 511, 146, 528, 163, 268, 365, INF, 432, 207],
        [482, 195, 328, 317, 277, 328, 140, 432, INF, 436],
        [233, 496, 146, 497, 207, 114, 573, 207, 436, INF],
    ]
    cost, path = solve_tsp(dist_matrix)
    named = [cities[i] for i in path]
    print(f"Optimal path: {' -> '.join(named)}")
    print(f"Total distance: {cost}")
