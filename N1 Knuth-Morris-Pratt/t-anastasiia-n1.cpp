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

// Функция для поиска подстроки с использованием алгоритма Кнута-Морриса-Пратта
int findSubstring(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();
    if (m == 0) {
        return 1;  // Пустая строка всегда найдена на первой позиции
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
            return i - m + 2;  // Позиции нумеруются с 1
        }
    }
    return -1;  // Если подстрока не найдена
}

int main() {
    // Перенаправление стандартного ввода и вывода на файлы
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    // Чтение входных данных
    string text, pattern;
    getline(cin, text);
    getline(cin, pattern);

    // Выполнение поиска подстроки
    int result = findSubstring(text, pattern);

    // Запись результата в файл
    cout << result;

    return 0;
}
