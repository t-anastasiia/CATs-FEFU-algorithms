#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void permute(vector<string>& dictionary, int l, int r, string ip, vector<string>& permutations) {
    if (l == r) {
        permutations.push_back(ip);
    } else {
        for (int i = l; i < r; i++) {
            if (l != 0 || i != 0) { // Добавить точку, если это не первый блок
                ip += ".";
            }
            ip += dictionary[i];
            permute(dictionary, l + 1, r, ip, permutations);
            ip.erase(ip.size() - dictionary[i].size() - (l != 0 || i != 0 ? 1 : 0)); // Удалить добавленный блок и точку
        }
    }
}


bool isValidIP(const string& ip) {
    cout << "IP: " << ip << endl;
    int count = 0;
    size_t start = 0;
    size_t pos = ip.find('.');
    while (pos != string::npos) {
        string sub = ip.substr(start, pos - start);
        cout << "Sub: " << sub << endl;
        if (sub.empty() || (sub.size() > 1 && sub[0] == '0') || stoi(sub) > 255) {
            return false;
        }
        start = pos + 1;
        pos = ip.find('.', start);
        count++;
    }
    string lastSub = ip.substr(start);
    cout << "Last sub: " << lastSub << endl;
    if (lastSub.empty() || (lastSub.size() > 1 && lastSub[0] == '0') || stoi(lastSub) > 255) {
        return false;
    }
    count++;
    cout << "Count: " << count << endl;
    return count == 4;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);

    vector<string> dictionary(4);
    for (int i = 0; i < 4; i++) {
        cin >> dictionary[i];
    }

    vector<string> permutations;
    permute(dictionary, 0, 4, "", permutations);

    for (const string& ip : permutations) {
        if (isValidIP(ip)) {
            cout << ip << endl;
        }
    }

    return 0;
}
