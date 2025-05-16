from math import inf

keys = [10, 20, 30, 40]
frequency = [4, 2, 6, 3]

num_keys = len(keys)

range_sum = [[0] * num_keys for i in range(num_keys)]
for i in range(num_keys):
    range_sum[i][i] = frequency[i]
    j = i + 1
    while j < num_keys:
        range_sum[i][j] = range_sum[i][j - 1] + frequency[j]
        j += 1

dp = [[0] * num_keys for i in range(num_keys)]

for i in range(num_keys):
    dp[i][i] = frequency[i]

for h in range(1, num_keys):
    for i in range(num_keys - h):
        j = h + i
        
        minimum_search_cost = inf
        for k in range(i, j + 1):
            left_cost = dp[i][k - 1] if k > i else 0
            right_cost = dp[k + 1][j] if k < j else 0
            kth_cost = left_cost + right_cost + range_sum[i][j]
            minimum_search_cost = min(minimum_search_cost, kth_cost)
        dp[i][j] = minimum_search_cost

for row in dp:
    print(row)
