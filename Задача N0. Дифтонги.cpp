#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool isVowel(char letter) {
    switch(letter) {
        case 'a':
            return true;
        case 'o':
            return true;
        case 'i':
            return true;
        case 'e':
            return true;
        case 'u':
            return true;
        case 'y':
            return true;
        default:
            return false;
    }
}

int countDiftongs(const string& word) {
    int diftongsAmount = 0;

    if(word.length() == 2) {
        if(isVowel(word[0]) && isVowel(word[1])) {
            return 1;
        }
        else {
            return 0;
        }
    }

    if(word.length() == 3) {
        if((isVowel(word[0]) && isVowel(word[1]) && !isVowel(word[2]))||
           (!isVowel(word[0]) && isVowel(word[1]) && isVowel(word[2]))) {
            return 1;
        } else {
            return 0;
        }
    }

    for(int i = 0; i < word.length()-2 ; i++) {
        if (i == 0) {
            if (isVowel(word[i]) && isVowel(word[i + 1]) && !isVowel(word[i + 2])) {
                diftongsAmount += 1;
            }
            continue;
        }

        if(!isVowel(word[i-1]) && isVowel(word[i]) && isVowel(word[i+1]) && !isVowel(word[i+2])) {
            diftongsAmount += 1;
        }
    }

    int len = word.length()-1;
    if(!isVowel(word[len-2]) && isVowel(word[len-1]) && isVowel(word[len])) {
        diftongsAmount += 1;
    }

    return diftongsAmount;
}


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    cin >> n;

    int maxDiftongs = 0;

    vector<string> resultWords;

    for(int i = 0; i < n; i++) {
        string word;
        cin >> word;

        if(maxDiftongs == 0 && word.length()) {
            resultWords.push_back(word);
        }

        if(word.length() >= 2) {

            int diftongs = countDiftongs(word);

            if (diftongs == maxDiftongs && diftongs != 0) {
                resultWords.push_back(word);
            } else if (diftongs > maxDiftongs) {
                maxDiftongs = diftongs;
                resultWords.clear();
                resultWords.push_back(word);
            }
        }
    }

    for(const auto & resultWord : resultWords) {
        cout << resultWord << "\n";
    }

    if(resultWords.empty()){
        cout << "-1";
    }

}
