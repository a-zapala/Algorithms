#include <iostream>

using namespace std;
int liczbaJedynek = 0;
constexpr int MAXN = 500020;
bool tab[MAXN];

int main() {
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    int a[MAXN];
    
    for (int j = 0; j < n; ++j) {
        cin >> a[j];
    }
    
    int poz;
    for ( int i = 0 ; i < n; i++) {
        poz = a[i];
        while(tab[poz]) {
            tab[poz] = false;
            poz++;
            liczbaJedynek--;
        }
        tab[poz] = true;
        liczbaJedynek++;
        cout << liczbaJedynek << endl;
    }
}