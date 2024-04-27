#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

void countingSort(vector<pair<int, int> >& numbers, int minVal, int maxVal) {
    vector<int> counts(maxVal - minVal + 1, 0);

    for (auto& number : numbers) {
        counts[number.first - minVal]++;
    }

    // Вычисляем сумму префиксов для получения правильных индексов вторых значений
    for (int i = 1; i < counts.size(); i++) {
        counts[i] += counts[i - 1];
    }

    vector<pair<int, int> > sortedNumbers(numbers.size());

    for (int i = numbers.size() - 1; i >= 0; i--) {
        int index = counts[numbers[i].first - minVal] - 1;
        sortedNumbers[index] = numbers[i];
        counts[numbers[i].first - minVal]--;
    }

    for (int i = 0; i < numbers.size(); i++) {
        numbers[i] = sortedNumbers[i];
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    cin >> n;

    vector<pair<int, int> > nums(n);

    int min = pow(10, 5), max = 0;

    for (int i = 0; i < n; i++) {
        cin >> nums[i].first >> nums[i].second;
        min = nums[i].first < min ? nums[i].first : min;
        max =nums[i].first > max ? nums[i].first : max;
    }

    countingSort(nums, min, max);

    for (const auto& pair : nums) {
        cout << pair.second << " ";
    }

    return 0;
}
