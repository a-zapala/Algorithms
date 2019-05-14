#include <iostream>

using namespace std;
constexpr int MAXN = 100000;

int main() {
    int n;
    int tab[MAXN];
    long long dp[MAXN][4][2];
    
    cin >> n;
    
    
    for (int i = 0; i < n; ++i) {
        cin >> tab[i];
    }
    
    dp[0][1][0] = tab[0];
    long long w;
    
    for (int i = 1; i < n; i++) {
        for (int k = 0; k < 4; k++)
            for (int t = 0; t < 2; t++) {
                w =0;
                if (k == 0) {
                    w = max( dp[i - 1][1][t], dp[i - 1][2][t]);
                    w = max (w, dp[i-1][0][t]);
                    if (t == 1) {
                        w = max(w, dp[i - 1][3][1]);
                    }
                }
                
                if (k == 1 || k == 2) {
                    w = dp[i - 1][k - 1][t] + tab[i];
                }
                
                if (k == 3 && t == 1) {
                    w = dp[i - 1][2][0] + tab[i];
                }
                
                dp[i][k][t] = w;
            }
    }
    w = 0;
    for (int j = 0; j < 4; ++j) {
        for (int i = 0; i < 2; ++i) {
            w = max(dp[n - 1][j][i], w);
        }
    }
    
    cout << w;
}