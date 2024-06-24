#include <iostream>
#include <cmath>

using namespace std;

const unsigned long long MODULO = 1000000007;

unsigned long long modularExponentiation(unsigned long long base, unsigned long long exponent, unsigned long long mod) {
    unsigned long long result = 1;
    base %= mod;
    while (exponent > 0) {
        if (exponent & 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exponent >>= 1;
    }
    return result;
}

unsigned long long factorialMod(int n, unsigned long long mod) {
    unsigned long long result = 1;
    for (int i = 1; i <= n; ++i) {
        result = (result * i) % mod;
    }
    return result;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    long long xStart, yStart, zStart, xEnd, yEnd, zEnd;
    cin >> xStart >> yStart >> zStart >> xEnd >> yEnd >> zEnd;

    int deltaX = abs(xEnd - xStart);
    int deltaY = abs(yEnd - yStart);
    int deltaZ = abs(zEnd - zStart);

    int totalSteps = deltaX + deltaY + deltaZ;

    unsigned long long factTotal = factorialMod(totalSteps, MODULO);
    unsigned long long invFactDeltaX = modularExponentiation(factorialMod(deltaX, MODULO), MODULO - 2, MODULO);
    unsigned long long invFactDeltaY = modularExponentiation(factorialMod(deltaY, MODULO), MODULO - 2, MODULO);
    unsigned long long invFactDeltaZ = modularExponentiation(factorialMod(deltaZ, MODULO), MODULO - 2, MODULO);

    unsigned long long paths = (factTotal * invFactDeltaX) % MODULO;
    paths = (paths * invFactDeltaY) % MODULO;
    paths = (paths * invFactDeltaZ) % MODULO;

    cout << paths << endl;

    return 0;
}
