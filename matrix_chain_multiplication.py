from math import inf

dimensions = [3, 2, 4, 2, 5]
num_matrices = len(dimensions) - 1

dp = [[0] * num_matrices for i in range(num_matrices)]

'''
   0  1  2
0 [0, 0, 0],
1 [0, 0, 0],
2 [0, 0, 0]
'''
for h in range(1, num_matrices):
    for i in range(num_matrices - h):
        j = h + i
        
        minimum_multiplication_cost = inf
        for k in range(i, j):
            kth_cost = dp[i][k] + dp[k+1][j] + dimensions[i] * dimensions[k+1] * dimensions[j+1]
            minimum_multiplication_cost = min(minimum_multiplication_cost, kth_cost)
        dp[i][j] = minimum_multiplication_cost
        
for row in dp:
    print(row)
