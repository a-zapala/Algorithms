#include <iostream>
#include <vector>
#include <map>
#include <bitset>
#include <set>

using namespace std;
typedef bitset<64> historia;
typedef int numer;


int main() {
    int n,m;
    cin >> n;
    cin >> m;
    
    
    map<numer,historia> mapa;
    
    int x;
    
    for (int i = 0; i < m; ++i) {
        vector<int> druzyna1;
        vector<int> druzyna2;
        for (int j = 0; j < n / 2; ++j) {
           cin >> x;
           druzyna1.push_back(x);
        }
        for (int j = 0; j < n/2; ++j) {
            cin >> x;
           druzyna2.push_back(x);
        }
        
        for( int numer : druzyna1) {
            mapa[numer][i] = true;
        }
        
        for( int numer : druzyna2) {
            mapa[numer][i] = false;
        }
    }
    
    set<unsigned long long> zbior;
    
    for( auto item : mapa) {
        if (!zbior.insert(item.second.to_ullong()).second){
            cout << "NIE";
            return 0;
        }
    }
    
    
    
    cout << "TAK";
    return 0;
    
}