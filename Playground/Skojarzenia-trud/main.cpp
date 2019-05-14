#include <iostream>
#include <vector>

using namespace std;

constexpr int MAXN = 300002;
vector<pair<int, int>> sasiedzi[MAXN];

int maks[MAXN];
int maks_bez[MAXN];

void DFS(int u, int o)
{
    for (auto v  : sasiedzi[u]) {
        if (v.first != o)
            DFS(v.first, u);
    }
    maks_bez[u] = 0;

    for (auto v  : sasiedzi[u]) {
        if (v.first != o)
            maks_bez[u] += maks[v.first];
    }

    maks[u] = maks_bez[u];
    for (auto v  : sasiedzi[u]) {
        if (v.first != o) {
            int tmp = maks_bez[u];
            tmp-=maks[v.first];
            tmp+=maks_bez[v.first];
            tmp+=v.second;
            maks[u] = max(maks[u],tmp);
        }

    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 0; i < n-1; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        sasiedzi[a].emplace_back(b, w);
        sasiedzi[b].emplace_back(a, w);
    }

    DFS(1,-1);

    cout << maks[1];


}