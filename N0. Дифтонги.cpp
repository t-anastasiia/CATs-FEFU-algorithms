//Задача N0. Дифтонги
//        Автор:	А. Кленин	 	Ограничение времени:	1 сек
//        Входной файл:	input.txt	 	Ограничение памяти:	64 Мб
//        Выходной файл:	output.txt
//        Условие
//Слова марсианского языка состоят из малых латинских букв. Буквы a, e, i, o, u, y считаются гласными, остальные — согласными.
//
//Дифтонгом называется пара подряд идущих гласных букв, окружённых либо согласными буквами, либо границами слова. Например, в слове preemptio имеется два дифтонга, а в слове aaa — ни одного.
//
//Требуется среди N данных слов найти те, в которых количество дифтонгов максимально.
//
//Формат входного файла
//        Первая строка входного файла содержит целое число N. Следующие N строк содержат по одному слову каждая.
//Формат выходного файла
//        Выходной файл должен содержать слова из входного файла, содержащие максимальное количество дифтонгов, по одному слову в строке. Слова должны располагаться в том же порядке, что и во входном файле.
//Ограничения
//1≤N≤100
//Слова содержат от 1 до 255 символов.
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
