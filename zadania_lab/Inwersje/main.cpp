#include <iostream>

constexpr int MAXN = 20000;
constexpr int MAXK = 10;
constexpr int mod = 1000000000;

int per[MAXN];
int inw[MAXK][MAXN];
int przedz[2 * MAXN];

int n, k;

using namespace std;

void insert(int x, int val) {
    int v = n - 1 + x;
    przedz[v] = val;
    while (v != 1) {
        v /= 2;
        przedz[v] = przedz[2 * v] + przedz[2 * v + 1];
        przedz[v] = przedz[v] % mod;
    }
}

int query(int a, int b) {
    int va = n - 1 + a, vb = n - 1 + b;
    /* Skrajne przedziały do rozkładu. */
    int wyn = przedz[va];
    if (va != vb) {
        wyn += przedz[vb];
        wyn = wyn % mod;
    }
    /* Spacer aż do momentu spotkania. */
    while (va / 2 != vb / 2) {
        if (va % 2 == 0) {
            wyn += przedz[va + 1];
            wyn = wyn % mod;
        }/* prawa bombka na lewej ścieżce */
        if (vb % 2 == 1) {
            wyn += przedz[vb - 1]; /* lewa bombka na prawej ścieżce */
            wyn = wyn % mod;
        }
        va /= 2;
        vb /= 2;
    }
    return wyn;
}

void clean() {
    for (int i = 0; i < 2 * n; ++i) {
        przedz[i] = 0;
    }
}

int main() {
    
    cin >> n;
    cin >> k;
    
    for (int i = 0; i < n; ++i) {
        cin >> per[i];
    }
    
    for (int j = 0; j < n; ++j) {
        inw[0][j] = 1;
    }
    
    for (int j = 1; j < k; ++j) {
        clean();
        for (int i = 0; i < n; ++i) {
            inw[j][i] = query(per[i], n);
            insert(per[i],inw[j-1][i]);
        }
    }
    
    long long sum = 0;
    
    for (int i = 0; i < n; ++i) {
        sum += inw[k - 1][i];
        sum = sum % mod;
    }
    
    cout << sum;
}