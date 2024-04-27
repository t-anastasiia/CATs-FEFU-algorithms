#include <iostream>
#include <vector>
#include <string>

using namespace std;

void bucketSort(vector<string>& arr, int n) {
    vector<vector<string> > buckets(52);

    for (int letter = 2; letter >= 0; --letter) {
        for(int i = 0; i < n; ++i) {
            char currentChar = arr[i][letter];
            int bucketIndex = (currentChar >= 'a') ? currentChar - 'a' + 26 : currentChar - 'A';
            buckets[bucketIndex].push_back(arr[i]);
        }

        int index = 0;
        for (int i = 0; i < 52; ++i) {
            for (const auto& str : buckets[i]) {
                arr[index++] = str;
            }
            buckets[i].clear();
        }
    }
}


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    cin >> n;

    vector<string> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    bucketSort(arr, n);

    for (int i = 0; i < n; ++i) {
        cout << arr[i] << "\n";
    }
    return 0;
}