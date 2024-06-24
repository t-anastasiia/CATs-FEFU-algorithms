#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    cin >> n;
    vector<int> sequence(n);
    for (int i = 0; i < n; i++) {
        cin >> sequence[i];
    }

    if (n == 1) {
        cout << 1 << "\n1";
        return 0;
    }

    vector<vector<int>> dp(n, vector<int>(n, 2));
    vector<vector<int>> prevIndex(n, vector<int>(n, -1));
    int maxLength = 2;
    pair<int, int> bestPair = {0, 1};

    for (int j = 1; j < n; j++) {
        for (int i = 0; i < j; i++) {
            int diff = sequence[j] - sequence[i];
            for (int k = 0; k < i; k++) {
                if (sequence[i] - sequence[k] == diff) {
                    if (dp[k][i] + 1 > dp[i][j]) {
                        dp[i][j] = dp[k][i] + 1;
                        prevIndex[i][j] = k;
                    }
                }
            }
            if (dp[i][j] > maxLength) {
                maxLength = dp[i][j];
                bestPair = {i, j};
            }
        }
    }

    vector<int> result;
    int i = bestPair.first;
    int j = bestPair.second;
    result.push_back(j + 1);
    while (i != -1) {
        result.push_back(i + 1);
        int temp = prevIndex[i][j];
        j = i;
        i = temp;
    }

    cout << maxLength << "\n";
    for (int k = result.size() - 1; k >= 0; k--) {
        cout << result[k] << " ";
    }

    return 0;
}
