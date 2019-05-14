#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;
constexpr int MAXN = 100000;
int n, l;
vector<int> tab[MAXN];

int main()
{
    unordered_map<int, pair<int,int>> mapa;
    ios_base::sync_with_stdio(0);
    cin >> n >> l;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < l; ++j) {
            int x;
            cin >> x;
            tab[i].push_back(x);
        }
    }
    int maxV = 1;

    for (int k = 0; k < l; ++k) {
        for (int i = 0; i < n; ++i) {
            int e = tab[i][k];
            if(mapa.find(e) == mapa.end()) {
                mapa[e].first = 1;
                mapa[e].second = k;
            } else {
                if(mapa[e].second == k-1) {
                    mapa[e].first = mapa[e].first + 1;
                    mapa[e].second = k;
                    maxV = max(mapa[e].first,maxV);
                } else if (mapa[e].second < k-1) {
                    mapa[e].first = 1;
                    mapa[e].second = k;
                }
            }
        }
    }
    cout << maxV;
}