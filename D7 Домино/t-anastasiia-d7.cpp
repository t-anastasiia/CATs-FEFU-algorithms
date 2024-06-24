#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

bool createDominoChain(const vector<pair<char, char>>& dominoes, vector<bool>& visited, vector<pair<char, char>>& chain, char end) {
    if (chain.size() == dominoes.size()) {
        return true;
    }

    for (size_t i = 0; i < dominoes.size(); ++i) {
        if (!visited[i]) {
            pair<char, char> domino = dominoes[i];
            if (domino.first == end || domino.second == end) {
                visited[i] = true;
                if (domino.first == end) {
                    chain.push_back(domino);
                    if (createDominoChain(dominoes, visited, chain, domino.second)) {
                        return true;
                    }
                } else {
                    chain.push_back(pair<char, char>(domino.second, domino.first));
                    if (createDominoChain(dominoes, visited, chain, domino.first)) {
                        return true;
                    }
                }
                chain.pop_back();
                visited[i] = false;
            }
        }
    }

    return false;
}

vector<pair<char, char>> parseDominoes(const string& input) {
    vector<pair<char, char>> dominoes;
    for (size_t i = 0; i < input.length(); i += 2) {
        pair<char, char> domino(input[i], input[i + 1]);
        dominoes.push_back(domino);
    }
    return dominoes;
}

void outputChain(const vector<pair<char, char>>& chain) {
    for (size_t i = 0; i < chain.size(); ++i) {
        if (i > 0) {
            cout << "-";
        }
        cout << chain[i].first << chain[i].second;
    }
    cout << endl;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    string input;
    cin >> input;

    vector<pair<char, char>> dominoes = parseDominoes(input);
    vector<bool> visited(dominoes.size(), false);
    vector<pair<char, char>> chain;

    for (size_t i = 0; i < dominoes.size(); ++i) {
        visited[i] = true;
        chain.push_back(dominoes[i]);
        if (createDominoChain(dominoes, visited, chain, dominoes[i].second)) {
            outputChain(chain);
            return 0;
        }
        chain.pop_back();
        visited[i] = false;

        chain.push_back(pair<char, char>(dominoes[i].second, dominoes[i].first));
        visited[i] = true;
        if (createDominoChain(dominoes, visited, chain, dominoes[i].first)) {
            outputChain(chain);
            return 0;
        }
        chain.pop_back();
        visited[i] = false;
    }

    cout << "NO" << endl;
    return 0;
}
