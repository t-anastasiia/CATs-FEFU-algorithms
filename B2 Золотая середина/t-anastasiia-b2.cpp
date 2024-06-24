#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

// Custom function to maintain the heap property while inserting an element
template <typename RandomIt, typename Compare>
void push_heap_custom(RandomIt first, RandomIt last, Compare comp) {
    auto dist = distance(first, last);
    if (dist > 1) {
        auto parentIdx = (dist - 2) / 2;
        auto childIdx = dist - 1;
        while (childIdx > 0 && comp(*(first + parentIdx), *(first + childIdx))) {
            swap(*(first + parentIdx), *(first + childIdx));
            childIdx = parentIdx;
            parentIdx = (childIdx - 1) / 2;
        }
    }
}

// Custom function to maintain the heap property while removing the root element
template <typename RandomIt, typename Compare>
void pop_heap_custom(RandomIt first, RandomIt last, Compare comp) {
    if (last - first > 1) {
        swap(*first, *(last - 1));
        auto dist = distance(first, last - 1);
        auto parentIdx = 0;
        while (true) {
            auto leftChildIdx = 2 * parentIdx + 1;
            auto rightChildIdx = 2 * parentIdx + 2;
            if (leftChildIdx >= dist) {
                break;
            }
            auto maxChildIdx = (rightChildIdx < dist && comp(*(first + leftChildIdx), *(first + rightChildIdx))) ? rightChildIdx : leftChildIdx;
            if (comp(*(first + parentIdx), *(first + maxChildIdx))) {
                swap(*(first + parentIdx), *(first + maxChildIdx));
                parentIdx = maxChildIdx;
            } else {
                break;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ifstream in("input.txt");
    ofstream out("output.txt");

    int n;
    in >> n;

    vector<int> a(n), lH, rH;

    for (int i = 0; i < n; ++i) {
        in >> a[i];
    }

    for (int i = 0; i < n; ++i) {
        if (lH.empty() || a[i] <= lH.front()) {
            lH.push_back(a[i]);
            push_heap_custom(lH.begin(), lH.end(), less<int>());
        } else {
            rH.push_back(a[i]);
            push_heap_custom(rH.begin(), rH.end(), greater<int>());
        }

        while (lH.size() < rH.size()) {
            lH.push_back(rH.front());
            push_heap_custom(lH.begin(), lH.end(), less<int>());
            pop_heap_custom(rH.begin(), rH.end(), greater<int>());
            rH.pop_back();
        }

        while (lH.size() > rH.size() + 1) {
            rH.push_back(lH.front());
            push_heap_custom(rH.begin(), rH.end(), greater<int>());
            pop_heap_custom(lH.begin(), lH.end(), less<int>());
            lH.pop_back();
        }

        out << lH.front() << '\n';
    }

    return 0;
}
