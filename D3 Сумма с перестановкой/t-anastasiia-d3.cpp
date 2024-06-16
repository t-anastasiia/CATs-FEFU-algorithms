//
// Created by Анастасия Талмазан on 2024-06-17.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Функция для извлечения цифр из числа
vector<int> extractDigits(long long n) {
    vector<int> digits;
    vector<int> tempDigits;
    while (n > 0) {
        tempDigits.push_back(n % 10);
        n /= 10;
    }
    for (auto it = tempDigits.rbegin(); it != tempDigits.rend(); ++it) {
        digits.push_back(*it);
    }
    return digits;
}

// Реализация быстрой сортировки
void quickSort(vector<long long> &arr, int left, int right) {
    int i = left, j = right;
    long long pivot = arr[(left + right) / 2];

    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) {
            // Перестановка без использования swap
            long long temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }

    if (left < j) quickSort(arr, left, j);
    if (i < right) quickSort(arr, i, right);
}

// Функция для генерации всех уникальных перестановок цифр числа без лидирующих нулей
void generatePermutations(vector<int> &digits, int l, int r, vector<long long> &permutations) {
    if (l == r) {
        if (digits[0] != 0) { // Проверка на отсутствие лидирующих нулей
            long long num = 0;
            for (int digit : digits) {
                num = num * 10 + digit;
            }
            permutations.push_back(num);
        }
        return;
    }
    for (int i = l; i <= r; ++i) {
        // Пропуск дубликатов
        bool duplicate = false;
        for (int j = l; j < i; ++j) {
            if (digits[j] == digits[i]) {
                duplicate = true;
                break;
            }
        }
        if (duplicate) continue;

        // Перестановка без использования swap
        int temp = digits[l];
        digits[l] = digits[i];
        digits[i] = temp;

        generatePermutations(digits, l + 1, r, permutations);

        // Восстановление порядка
        temp = digits[l];
        digits[l] = digits[i];
        digits[i] = temp;
    }
}

// Функция для проверки, равна ли сумма двух чисел заданному числу
bool checkSum(vector<long long> &a_permutations, vector<long long> &b_permutations, long long target) {
    quickSort(a_permutations, 0, a_permutations.size() - 1);
    quickSort(b_permutations, 0, b_permutations.size() - 1);

    int i = 0, j = b_permutations.size() - 1;

    while (i < a_permutations.size() && j >= 0) {
        long long sum = a_permutations[i] + b_permutations[j];
        if (sum == target) {
            cout << "YES" << endl;
            cout << a_permutations[i] << " " << b_permutations[j] << endl;
            return true;
        } else if (sum < target) {
            i++;
        } else {
            j--;
        }
    }
    return false;
}

int main() {
    // Перенаправление стандартного ввода и вывода на файлы
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    long long a, b, c;
    cin >> a >> b >> c;

    vector<int> a_digits = extractDigits(a);
    vector<int> b_digits = extractDigits(b);

    vector<long long> a_permutations, b_permutations;

    generatePermutations(a_digits, 0, a_digits.size() - 1, a_permutations);
    generatePermutations(b_digits, 0, b_digits.size() - 1, b_permutations);

    if (!checkSum(a_permutations, b_permutations, c)) {
        cout << "NO" << endl;
    }

    return 0;
}
