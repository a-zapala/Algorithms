#include <iostream>
#include <vector>
#include <list>

using namespace std;

int n;

constexpr int MAXN = 500002;
vector<int> sasiedzi[MAXN];
long long int suma[MAXN];
long long int suma_wszystkich[MAXN];
int ilosc_w_podrzewie[MAXN];
int ojciec[MAXN];

void DFS(int i, int o)
{
    ojciec[i] = o;
    for (auto p : sasiedzi[i]) {
        if (p != o)
            DFS(p, i);
    }

    for (auto p  : sasiedzi[i]) {
        if (p != o) {
            ilosc_w_podrzewie[i] += max(ilosc_w_podrzewie[i],ilosc_w_podrzewie[p]);
        }
    }
    ilosc_w_podrzewie[i]++;
}

list<int> kol;

void BFS(int i)
{
    kol.push_back(i);
    while (!kol.empty()) {
        int v = kol.front();
        kol.pop_front();
        if (v != 1)
            suma_wszystkich[1] = suma_wszystkich[ojciec[v]] + n - 2 * ilosc_w_podrzewie[v];

        for (auto u  : sasiedzi[v]) {
            if (u != ojciec[v])
                kol.push_back(u);
        }
    }
}

int main()
{
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        sasiedzi[a].push_back(b);
        sasiedzi[b].push_back(a);
    }

    DFS(1, -1);
    suma[1] = ilosc_w_podrzewie[1];
    BFS(1);

    for (int j = 1; j <= n; ++j) {
        cout << suma_wszystkich[j]<<endl;
    }
    return 0;
}