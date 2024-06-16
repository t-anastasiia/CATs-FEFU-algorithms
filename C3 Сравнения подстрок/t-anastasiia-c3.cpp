//
// Created by Анастасия Талмазан on 2024-06-17.
//
#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;
const int P = 31; // Простое основание для хеширования
const int MOD = 1e9 + 9; // Большое простое число для модуля

// Функция для вычисления хешей для всех префиксов строки
vector<ll> compute_hashes(const string& s) {
    int n = s.size();
    vector<ll> hashes(n + 1, 0);
    vector<ll> powers(n + 1, 1);

    for (int i = 0; i < n; i++) {
        hashes[i + 1] = (hashes[i] * P + (s[i] - 'a' + 1)) % MOD;
        powers[i + 1] = (powers[i] * P) % MOD;
    }

    return hashes; // Возвращаем массив хешей
}

// Функция для получения хеша подстроки
ll get_hash(int l, int r, const vector<ll>& hashes, const vector<ll>& powers) {
    ll hash_value = (hashes[r + 1] - hashes[l] * powers[r - l + 1]) % MOD;
    if (hash_value < 0) hash_value += MOD;
    return hash_value;
}

int main() {
    string s;
    cin >> s;

    int m;
    cin >> m;

    vector<ll> hashes = compute_hashes(s);
    vector<ll> powers(s.size() + 1, 1);
    for (int i = 1; i <= s.size(); i++) {
        powers[i] = (powers[i - 1] * P) % MOD;
    }

    while (m--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        --a; --b; --c; --d; // Перевод в 0-индексацию

        if (b - a != d - c) {
            cout << "No\n";
        } else {
            ll hash1 = get_hash(a, b, hashes, powers);
            ll hash2 = get_hash(c, d, hashes, powers);

            if (hash1 == hash2) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        }
    }

    return 0;
}
