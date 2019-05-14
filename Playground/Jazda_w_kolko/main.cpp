#include <iostream>
#include <vector>
#include <set>

using namespace std;

constexpr int MAXN = 500002;
vector<int> sasiedzi[MAXN];
bool visited[MAXN];
bool samochod[MAXN];
set<int> zbior;

void DFS(int u)
{
    visited[u] = true;

    if (samochod[u]) {
        zbior.insert(u);
        return;
    }

    for (auto v : sasiedzi[u]) {
        if (!visited[v]) {
            DFS(v);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    int n, m;

    cin >> n >> m;

    for (int j = 1; j <= n; ++j) {
        int x;
        cin >> x;
        if (x) {
            samochod[j] = true;
        }
    }

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        sasiedzi[a].push_back(b);
        sasiedzi[b].push_back(a);
    }

    DFS(1);

    for (auto v  : zbior)
        cout << v << endl;
}