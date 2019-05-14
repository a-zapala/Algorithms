#include <iostream>
#include <vector>
#include <queue>

using namespace std;

constexpr int MAXN = 100001;

int koszt[MAXN];
int ile_zaleznosci[MAXN];
vector<int> zalezne[MAXN];

struct compare {
    bool operator()(const pair<int,int> pair1, const pair<int,int> pair2) const {
        return pair1.first > pair2.first;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    int n,m,k;
    
    cin>>n;
    cin>>m;
    cin>>k;
    
    for (int i = 1; i <= n; ++i) {
        cin >> koszt[i];
        ile_zaleznosci[i] = 0;
    }
    
    for (int j = 0; j < m; ++j) {
        int a,b;
        cin >> a;
        cin >> b;
        ile_zaleznosci[a]++;
        zalezne[b].push_back(a);
    }
    priority_queue<pair<int,int>, vector<pair<int,int>>, compare> kolejka;
    
    for (int i = 1; i <=n ; ++i) {
        if(ile_zaleznosci[i] == 0) {
            kolejka.push(make_pair(koszt[i],i));
        }
    }
    
    int aktualnaIlosc = 0;
    int maxKoszt = 0;
    
    for (int i = 0; i < k; ++i) {
        auto value = kolejka.top();
        kolejka.pop();
        
        if(maxKoszt < value.first)
            maxKoszt = value.first;
        
        for ( auto nowy: zalezne[value.second]) {
            ile_zaleznosci[nowy]--;
            if(ile_zaleznosci[nowy] == 0)
                kolejka.push(make_pair(koszt[nowy],nowy));
        }
    }
    
    cout << maxKoszt;
    
    
}