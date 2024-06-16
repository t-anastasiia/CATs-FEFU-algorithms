//
// Created by Анастасия Талмазан on 2024-06-17.
//
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

int main() {
    // Перенаправление стандартного ввода и вывода на файлы
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N;
    cin >> N;
    vector<char> pancakes(N);

    for (int i = 0; i < N; ++i) {
        cin >> pancakes[i];
    }

    int flips = 0;
    for (int i = 1; i < N; ++i) {
        if (pancakes[i] != pancakes[i - 1]) {
            flips++;
        }
    }

    // Если последний блин лежит подгоревшей стороной вверх (B), нужно дополнительное переворачивание
    if (pancakes[N - 1] == 'B') {
        flips++;
    }

    cout << flips << endl;

    return 0;
}
