#include <iostream>
#include <vector>

using namespace std;

constexpr int MAXN = 100005;
long long int wagi[MAXN][2];
long long int maks[MAXN];

int main()
{
    ios_base::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;

    if (n % 2 == 1) {
        cout << -1;
        return 0;
    }

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;

        if (u > v) {
            swap(u, v);
        }

        wagi[u][v - u - 1] = w;
    }

    maks[1] = -1;
    if (wagi[1][0])
        maks[1] = wagi[1][0];


    for (int i = 2; 2 * i <= n; ++i) {

        maks[i] = -1;

        if (maks[i - 1] != -1 && wagi[2 * i - 1][0]) {
            maks[i] = wagi[2 * i - 1][0] + maks[i - 1];
        }

        if (maks[i - 2] != -1 && wagi[2 * i - 3][1] && wagi[2 * i - 2][1]) {
            if (maks[i] == -1) {
                maks[i] = maks[i - 2] + wagi[2 * i - 3][1] + wagi[2 * i - 2][1];
            } else {
                maks[i] = min(maks[i], maks[i - 2] + wagi[2 * i - 3][1] + wagi[2 * i - 2][1]);
            }
        }
    }

    cout << maks[n / 2];

    return 0;
}