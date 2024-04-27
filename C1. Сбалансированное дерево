#include <iostream>
#include <set>

using namespace std;

int main() {
    freopen("input.txt", "r", stdin);

    freopen("output.txt", "w", stdout);
    
    set<int> numbers;

    int num;
    while (cin >> num) {
        if (num > 0) {
            numbers.insert(num);
        } else if (num < 0) {
            numbers.erase(-num);
        } else {
            for (int n : numbers) {
                cout << n << " ";
            }
            break;
        }
    }

    return 0;
}
