#include <iostream>
#include <climits>

using namespace std;

constexpr int MAXN = 1000003;

int main() {
    int m;
    int ceny[MAXN];
    int liczba[MAXN];
    long long suma[MAXN];
    int minEven[MAXN];
    int minOdd[MAXN];
    int maxOdd[MAXN];
    int maxEven[MAXN];
    int n;

    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> ceny[i];
    }

    cin >> m;
    for (int j = 0; j < m; ++j) {
        cin >> liczba[j];
    }

    suma[n - 1] = ceny[n - 1];

    for (int i = n - 2; i >= 0; --i) {
        suma[i] = suma[i + 1] + ceny[i];
    }

    minEven[n] = INT_MAX;
    minOdd[n] = INT_MAX;

    for (int i = n - 1; i >= 0; --i) {
        minEven[i] = minEven[i + 1];
        minOdd[i] = minOdd[i + 1];
        if (ceny[i] % 2 == 0) {
            minEven[i] = ceny[i];
        }
        else {
            minOdd[i] = ceny[i];
        }
    }

    maxEven[0] = INT_MIN;
    maxOdd[0] = INT_MIN;
    for (int i = 1; i < n; ++i) {
        maxEven[i] = maxEven[i - 1];
        maxOdd[i] = maxOdd[i - 1];
        if (ceny[i-1] % 2 == 0) {
            maxEven[i] = ceny[i - 1];
        }
        else {
            maxOdd[i] = ceny[i - 1];
        }
    }

    long long w1 = -1;
    long long w2 = -1;
    int index;
    for (int k = 0; k < m; ++k) {
        index = n - liczba[k];
        if (suma[index] % 2 == 0) {
            w1 = -1;
            w2 = -1;
            if ( maxEven[index] != INT_MIN
                && minOdd[index] != INT_MAX)
            {
                w1 = suma[index] + maxEven[index] - minOdd[index];
            }
            if ( maxOdd[index] != INT_MIN
                 && minEven[index] != INT_MAX)
            {
                w2 = suma[index] + maxOdd[index] - minEven[index];
            }
            cout << max(w1,w2) << endl;
        }
        else {
            cout << suma[index] << endl;
        }
    }

}