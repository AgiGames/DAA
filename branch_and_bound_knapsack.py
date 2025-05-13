from typing import List
import heapq

profits = [10, 10, 12, 18]
weights = [2, 4, 6, 9]
weight_limit = 15

items = list(zip(profits, weights))
num_items = len(items)

for i in range(num_items - 1):
    swapped = False
    for j in range(num_items - i - 1):
        jth_item_profit = items[j][0]
        jth_item_weight = items[j][1]

        j_plus_1th_item_profit = items[j+1][0]
        j_plus_1th_item_weight = items[j+1][1]

        jth_item_profit_to_weight_ratio = jth_item_profit / jth_item_weight
        j_plus_1th_item_profit_to_weight_ratio = j_plus_1th_item_profit / j_plus_1th_item_weight

        if jth_item_profit_to_weight_ratio < j_plus_1th_item_profit_to_weight_ratio:
            temp = items[j]
            items[j] = items[j+1]
            items[j+1] = temp
            swapped = True

    if not swapped:
        break

profits = [item[0] for item in items]
weights = [item[1] for item in items]

def calculate_upper_bound(include_exclude_bit_set: list[int]) -> int:
    profit_sum = 0
    weight_added_so_far = 0
    for i in range(len(include_exclude_bit_set)):
        if include_exclude_bit_set[i] == 1:
            if weight_added_so_far + weights[i] <= weight_limit:
                profit_sum += profits[i]
                weight_added_so_far += weights[i]
            else:
                profit_sum += (weight_limit - weight_added_so_far) * (profits[i] / weights[i])
                weight_added_so_far += (weight_limit - weight_added_so_far)
                break
    return profit_sum

def branch_bound_knapsack():

    max_profit = 0
    
    # profit, weight, item index, upper bound, include or exclude bit set
    starting_state = (0, 0, 0, [1] * num_items)
    heap = []
    heapq.heappush(heap, starting_state)

    while heap:
        profit, weight, item_idx, iebs = heapq.heappop(heap)

        if item_idx == num_items:
            continue

        upper = calculate_upper_bound(iebs)
        if upper < max_profit:
            continue


        if weight + weights[item_idx] <= weight_limit:
            inclusion_profit = profit + profits[item_idx]
            inclusion_weight = weight + weights[item_idx]
            max_profit = max(max_profit, inclusion_profit)
            inclusion_next_state = (inclusion_profit, inclusion_weight, item_idx + 1, iebs)
            heapq.heappush(heap, inclusion_next_state)

        exclusion_iebs = iebs.copy()
        exclusion_iebs[item_idx] = 0
        exclusion_next_state = (profit, weight, item_idx + 1, exclusion_iebs)
        heapq.heappush(heap, exclusion_next_state)

    return max_profit

print(branch_bound_knapsack())
