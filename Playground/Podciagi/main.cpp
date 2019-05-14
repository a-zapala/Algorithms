#include <iostream>
#include <set>
#include <unordered_map>

using namespace std;

constexpr int MAXN = 500002;
int tab[MAXN];

int main()
{
    int n, k;
    cin >> n >> k;

    for (int i = 0; i < n; ++i) {
        cin >> tab[i];
    }

    unordered_map<int, int> rozne;
    int i = 0;
    int j = 0;
    long long suma = 0;

    while (j < n) {
        rozne[tab[j]]++;

        while (rozne.size() > k) {
            rozne[tab[i]]--;
            if(rozne[tab[i]] == 0)
                rozne.erase(tab[i]);
            i++;
        }
        suma += j - i + 1;
        j++;
    }
    cout << suma;
    return 0;
}