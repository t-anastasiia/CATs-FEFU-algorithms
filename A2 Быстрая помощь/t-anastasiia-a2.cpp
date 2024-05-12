// Задача A2. Быстрая помощь
// Автор:	И. Лудов, А. Кленин	 	Ограничение времени:	2 сек
// Входной файл:	input.txt	 	Ограничение памяти:	64 Мб
// Выходной файл:	output.txt
//     Условие
// В городе В случилась катастрофа: неожиданно наступила зима. Чтобы облегчить судьбу жителей В, из города М решено
// направить N самолётов с тёплой одеждой.
// Самолёты имеют различную скорость, так что самолёт номер i затратит на полёт в точности ai минут.
// Разгрузка любого самолёта в аэропорту В занимает L минут, после чего аэропорт готов к приёму следующего самолёта.
//Аэропорт города М большой, и способен оправлять любое необходимое количество самолётов одновременно. Аэропорт города
// В, напротив, может принимать и разгружать самолёты только по одному. Самолёты могут взлетать в любом порядке, но
// не должны обгонять друг друга в воздухе, т. е. если самолёт 1 взлетел раньше самолёта 2 , то и приземлиться он
// должен раньше.
// Требуется определить минимальное время в минутах, требуемое на перелёт и разгрузку всех самолётов.
//      Формат входного файла
// Входной файла содержит целые числа N L, за которыми следуют N чисел ai — времена полёта в минутах.
//      Формат выходного файла
// Выходной файл должен содержать число — минимальное время до окончания разгрузки последнего самолёта в минутах.
//      Ограничения
// 1≤N≤10000;
// 1≤ai;
// L≤1000
#include <iostream>
#include <vector>
using namespace std;

void send_planes(int *planeTimes, int numPlanes) {
    for (int i = 0; i < numPlanes - 1; i++) {
        bool isSwapped = false;
        for (int j = 0; j < numPlanes - i - 1; j++) {
            if (planeTimes[j] > planeTimes[j + 1]) {
                swap(planeTimes[j], planeTimes[j + 1]);
                isSwapped = true;
            }
        }
        if (!isSwapped)
            break;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int numPlanes, unloadTime, totalTime = 0;
    cin >> numPlanes >> unloadTime;
    vector<int> planeTimes(numPlanes);

    for (int i = 0; i < numPlanes; i++) {
        cin >> planeTimes[i];
    }

    send_planes(planeTimes.data(), numPlanes);

    for (int i = 0; i < numPlanes; i++) {
        if (planeTimes[i] <= totalTime) {
            totalTime += unloadTime;
        } else {
            totalTime = planeTimes[i] + unloadTime;
        }
    }

    cout << totalTime;
    return 0;
}
