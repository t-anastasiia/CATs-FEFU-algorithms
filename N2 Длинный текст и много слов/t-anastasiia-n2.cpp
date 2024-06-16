//
// Created by Анастасия Талмазан on 2024-06-17.
//
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Функция для вычисления префикс-функции
vector<int> computePrefixFunction(const string& pattern) {
    int m = pattern.length();
    vector<int> pi(m, 0);
    int k = 0;
    for (int i = 1; i < m; ++i) {
        while (k > 0 && pattern[k] != pattern[i]) {
            k = pi[k - 1];
        }
        if (pattern[k] == pattern[i]) {
            ++k;
        }
        pi[i] = k;
    }
    return pi;
}

// Функция для поиска подстроки с использованием алгоритма KMP
bool isSubstring(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();
    if (m == 0) {
        return true;
    }
    vector<int> pi = computePrefixFunction(pattern);
    int q = 0;
    for (int i = 0; i < n; ++i) {
        while (q > 0 && pattern[q] != text[i]) {
            q = pi[q - 1];
        }
        if (pattern[q] == text[i]) {
            ++q;
        }
        if (q == m) {
            return true;
        }
    }
    return false;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    string text;
    cin >> text;

    int N;
    cin >> N;

    for (int i = 0; i < N; ++i) {
        string word;
        cin >> word;

        if (isSubstring(text, word)) {
            cout << "1 ";
        } else {
            cout << "0 ";
        }
    }

    return 0;
}
