#include <iostream>
#include <map>

using namespace std;
constexpr int MAXN = 500002;
int wart[MAXN];

long long kwadrat(int k1, int k2) { //najpierw wiekszy
    long long pom = (wart[k1]- wart[k2]);
    return  pom * pom;
}

int main() {

    int n;
    cin >> n;


    for (int i = 0; i < n; ++i) {
        cin >> wart[i];
    }

    map<int, pair<int,int>> mapa;

    if(n<2){
        return 0;
    }

    long long suma;
    int indeksWiekszego;
    int indeksMniejszego;

    if ( wart[0] > wart[1]) {
        mapa[wart[0]] = make_pair(0,1);
        suma = kwadrat(0,1);
    } else {
        mapa[wart[1]] = make_pair(1,0);
        suma = kwadrat(1,0);
    }

    int actual;
    cout <<suma <<endl;
    for (int k = 2; k < n; ++k) {
        actual = wart[k];
        auto iter = mapa.lower_bound(actual);
        if ( iter == mapa.end()) {
            iter--;
            mapa[actual] = make_pair(k,iter->second.first);
            suma += kwadrat(k,iter->second.first);
        } else {
            if ( iter == mapa.begin()) {
                indeksWiekszego = iter->second.first;
                indeksMniejszego = iter->second.second;
                if( actual <= wart[indeksMniejszego]) {
                    mapa[wart[indeksMniejszego]] = make_pair(indeksMniejszego,k);
                    suma += kwadrat(indeksMniejszego,k);
                    cout << suma << endl;
                    continue;
                }
            }
            indeksWiekszego = iter->second.first;
            indeksMniejszego = iter->second.second;
            suma -= kwadrat(indeksWiekszego,indeksMniejszego);
            mapa.erase(iter);
            mapa[wart[indeksWiekszego]] = make_pair(indeksWiekszego,k);
            suma += kwadrat(indeksWiekszego,k);
            mapa[actual] = make_pair(k, indeksMniejszego);
            suma += kwadrat(k, indeksMniejszego);
        }

        cout<<suma<<endl;
    }

}