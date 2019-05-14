#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    int n;
    map<long long int, long long int> wys;



    cin >> n;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        wys[x]++;
    }

    int z;
    cin >> z;
    long long int liczbaKrokow = 0;
    for (int j = 0; j < z; ++j) {
        int x;
        cin >> x;
        while (liczbaKrokow < x) {
            auto it = prev(wys.end());
            long long int wart = it->first;

            liczbaKrokow += it->second;
            wys[wart / 2] += it->second;
            wys[wart - wart / 2] += it->second;
            wys.erase(it);
        }
        if(liczbaKrokow == x) {
            cout << wys.size() << endl;
        } else {
            cout << wys.size()+1 << endl;
        }
        liczbaKrokow-=x;
    }
}
