#include <iostream>

using namespace std;
constexpr int MAXN = 1003;



int main() {
    int n;
    
    cin >> n;
    
    if(n==1) {
        cout<<1;
        return 0;
    }
    
    int tab[MAXN];
    int c[MAXN][MAXN];
    int b[MAXN][MAXN][2];
    
    for (int i = 0; i < n; ++i) {
        cin >> tab[i];
    }
    
    for( int i = 0 ; i < n; ++i ) {
        for (int j = 0; j < n; ++j) {
            if ( tab[i] < tab[j]) {
                c[i][j]=1;
            } else {
                c[i][j] = 0;
            }
        }
    }
    
    for (int i = 0; i < n-1; ++i) {
        b[i][i+1][0] = c[i][i+1];
        b[i][i+1][1] = c[i][i+1];
    }
    
    long long w1;
    long long w2;
    
    for (int k = 2; k < n; ++k) {
        for (int p = k-2; p>=0 ; p--) {
            w1 = c[p][p+1]*b[p+1][k][0] + c[p][k]*b[p+1][k][1];
            b[p][k][0] = static_cast<int>(w1 % 1000000000);
            w2 = c[p][k]*b[p][k-1][0] + c[k-1][k]*b[p][k-1][1];
            b[p][k][1] = static_cast<int>(w2 % 1000000000);
        }
    }
    w1 = b[0][n-1][1] + b[0][n-1][0];
    
    cout << w1 % 1000000000;
    
}