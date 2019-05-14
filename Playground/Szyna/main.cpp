#include <iostream>
#include <unordered_set>

using namespace std;
constexpr int MAXN = 500000;
int tab[MAXN];

int n;

int main()
{
    unordered_set<int> zbior;
    int suma = 0;

    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> tab[i];
    }

    for (int j = 0; j < n; ++j) {
        if(zbior.find(tab[j]) != zbior.end()) {
            suma++;
            zbior.clear();
        } else {
            zbior.insert(tab[j]);
        }
    }

    cout << suma;
}