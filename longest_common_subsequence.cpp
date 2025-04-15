#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {

    string string_1;
    string string_2;

    cout << "Enter the first string: ";
    cin >> string_1;
    cout << "Enter the second string: ";
    cin >> string_2;

    int n = string_1.length();
    int m = string_2.length();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    vector<vector<string>> subsequence(n + 1, vector<string>(m + 1, ""));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {

            if (string_1[i - 1] == string_2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                string new_subsequence = subsequence[i - 1][j - 1];
                new_subsequence.push_back(string_1[i - 1]);
                subsequence[i][j] = new_subsequence;
            }

            else {
                dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);

                int compare_value_1 = dp[i][j - 1];
                int compare_value_2 = dp[i - 1][j];

                if (compare_value_1 > compare_value_2) {
                    dp[i][j] = dp[i][j - 1];
                    subsequence[i][j] = subsequence[i][j - 1];
                }

                else {
                    dp[i][j] = dp[i - 1][j];
                    subsequence[i][j] = subsequence[i - 1][j];
                }

            }

        }
    }

    cout << "Maximum Common Subsequence Length: " << dp[n][m] << "\n";
    cout << "Maximum Common Subsequence: " << subsequence[n][m] << "\n";

    return 0;

}
