#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int MAXN = 500003;
bool visited[MAXN];
vector<pair<int, int>> sasiedzi[MAXN];
long long int suma;

bool myfunction(pair<int, int> i, pair<int, int> j)
{
    return (i.first < j.first);
}

void DFS(int u)
{
    visited[u] = true;
    int prev_w = 0;
    long long int ilos_mniejszych = 0;

    for (int i = 0; i < sasiedzi[u].size(); ++i) {
        if (prev_w != sasiedzi[u][i].first) {
            ilos_mniejszych = i;
            prev_w = sasiedzi[u][i].first;
        }
        suma += ilos_mniejszych;

        if (!visited[sasiedzi[u][i].second])
            DFS(sasiedzi[u][i].second);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        sasiedzi[u].emplace_back(w, v);
        sasiedzi[v].emplace_back(w, u);
    }

    for (int j = 1; j <= n; ++j) {
        visited[j] = false;
        sort(sasiedzi[j].begin(), sasiedzi[j].end(),myfunction);
    }

    suma = 0;

    for (int k = 1; k <= n; ++k) {
        if (!visited[k])
            DFS(k);
    }

    cout << suma;

    return 0;
}