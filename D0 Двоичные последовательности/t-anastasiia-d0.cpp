//
// Created by Анастасия Талмазан on 2024-06-17.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void generateBinarySequences(int n, string current, vector<string>& sequences) {
    if (current.size() == n) {
        sequences.push_back(current);
        return;
    }
    generateBinarySequences(n, current + "0", sequences);
    generateBinarySequences(n, current + "1", sequences);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N;
    cin >> N;

    vector<string> sequences;
    generateBinarySequences(N, "", sequences);

    for (const string& seq : sequences) {
        cout << seq << endl;
    }

    return 0;
}
