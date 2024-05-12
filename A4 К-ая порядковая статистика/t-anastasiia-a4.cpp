//Задача A4. K-ая порядковая статистика
//Автор:	StdAlg	 	Ограничение времени:	3 сек
//Входной файл:	input.txt	 	Ограничение памяти:	256 Мб
//Выходной файл:	output.txt
//      Условие
//K-ой порядковой статистикой N-элементной последовательности AN называется число AK, которое будет стоять на
//K-ом месте после упорядочивания элементов этой последовательности по возрастанию. Последовательность AN задаётся
// следующим образом. A1 = P, Ai = (Ai−1 ⋅ Q) mod V.
//      Формат входного файла
//Во входном файле содержатся целые числа Q V P N K
//      Формат выходного файла
//В выходном файле должно содержаться единственное число — K-ая порядковая статистика исходной последовательности.
//      Ограничения
//V,Q ≠ 0
//0 ≤ Q⋅ V, Q ⋅ P ≤ 2^31 − 1
//1 ≤ K ≤ N ≤ 4 ⋅ 10^7

#include <iostream>
using namespace std;

void swap(int &a, int &b) {
    int t = a;
    a = b;
    b = t;
}

int partition(int a[], int l, int r) {
    int x = a[r];
    int i = l;
    for (int j = l; j <= r - 1; j++) {
        if (a[j] <= x) {
            swap(a[i], a[j]);
            i++;
        }
    }
    swap(a[i], a[r]);
    return i;
}

int findOrderStatistics(int a[], int l, int r, int k) {
    if (k > 0 && k <= r - l + 1) {
        int pivot = partition(a, l, r);
        if (pivot - l == k - 1)
            return a[pivot];
        if (pivot - l > k - 1)
            return findOrderStatistics(a, l, pivot - 1, k);
        return findOrderStatistics(a, pivot + 1, r, k - pivot + l - 1);
    }
    return -1; // В случае некорректного ввода
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int q, v, p, n, k;
    cin >> q >> v >> p >> n >> k;
    int a[n];
    a[0] = p;
    for (int i = 1; i < n; ++i) {
        cin >> a[i];
        a[i] = (a[i - 1] * q) % v;
    }

    int result = findOrderStatistics(a, 0, n - 1, k);
    cout << result;
    return 0;
}
