#include <vector>
#include <climits>
#include <iostream>
using namespace std;

int solve_kanpsack(int weight_limit, vector<int> &item_values, vector<int> &item_weights) {

    int num_items = item_values.size();
    vector<vector<int>> dp(num_items + 1, vector<int> (weight_limit + 1));

    for (int i = 1; i < num_items + 1; i++) {
        for (int j = 1; j < weight_limit + 1; j++) {

            int inclusion_result = INT_MIN;
            if (item_weights[i - 1] <= j) {
                inclusion_result = item_values[i - 1] + dp[i - 1][j - item_weights[i - 1]];
            }

            int exclusion_result = dp[i - 1][j];

            dp[i][j] = (inclusion_result > exclusion_result)? inclusion_result: exclusion_result;

        }
    }

    return dp[num_items][weight_limit];

}

int main() {

    vector<int> item_values = {1, 2, 3};
    vector<int> item_weights = {4, 5, 1};
    int weight_limit = 4;

    cout << solve_kanpsack(weight_limit, item_values, item_weights) << endl;
    return 0;

}
