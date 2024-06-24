#include <iostream>
#include <vector>
#include <limits>

using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int numDishes, requiredSatiation;
    cin >> numDishes >> requiredSatiation;

    vector<int> dishCosts(numDishes), dishSatiation(numDishes);
    for (int i = 0; i < numDishes; ++i) {
        cin >> dishCosts[i] >> dishSatiation[i];
    }

    int maxSatiation = requiredSatiation * 100;
    const long long INFINITY = numeric_limits<long long>::max();

    vector<long long> minExpenditure(maxSatiation + 1, INFINITY);
    minExpenditure[0] = 0;

    for (int i = 0; i < numDishes; ++i) {
        for (int j = dishSatiation[i]; j <= maxSatiation; ++j) {
            if (minExpenditure[j - dishSatiation[i]] != INFINITY) {
                long long potentialCost = minExpenditure[j - dishSatiation[i]] + dishCosts[i];
                if (potentialCost < minExpenditure[j]) {
                    minExpenditure[j] = potentialCost;
                }
            }
        }
    }

    long long minTotalCost = INFINITY;
    for (int i = requiredSatiation; i <= maxSatiation; ++i) {
        if (minExpenditure[i] < minTotalCost) {
            minTotalCost = minExpenditure[i];
        }
    }

    cout << minTotalCost << endl;

    return 0;
}
