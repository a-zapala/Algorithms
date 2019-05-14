#include <iostream>
#include <vector>
#include <climits>
#include <tuple>
#include <set>

using namespace std;

constexpr int MAXN = 500002;

vector<int> czerwone[MAXN];
vector<int> zielone[MAXN];



int d_kon_czerwone[MAXN];
int d_kon_zielone[MAXN];

//tupla distance,nr, kolor ostatniego
struct compare {
    bool operator()(const tuple<int, int, bool> &lhs, const tuple<int, int, bool> &rhs) const {
        return lhs < rhs;
    }
};

set<tuple<int, int, bool>,compare> que;

void update_distance(int nr, bool k) {
    if(k) {
        for(auto v: czerwone[nr]){
            
            if(d_kon_zielone[v] > d_kon_czerwone[nr] + 1) {
                if (d_kon_zielone[v] != INT_MAX) {
                    que.erase(make_tuple(d_kon_zielone[v], v,0));
                }
                d_kon_zielone[v] = d_kon_czerwone[nr] + 1;
                que.emplace(d_kon_zielone[v],v,0);
            }
        }
    } else {
        for(auto v: zielone[nr]){
            if(d_kon_czerwone[v] > d_kon_zielone[nr] + 1) {
                if (d_kon_czerwone[v] != INT_MAX) {
                    que.erase(make_tuple(d_kon_czerwone[v], v,1));
                }
                d_kon_czerwone[v] = d_kon_zielone[nr] + 1;
                que.emplace(d_kon_czerwone[v],v,1);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int m, n;
    cin >> n >> m;
    
    
    for (int i = 0; i < m; ++i) {
        int a, b, k;
        cin >> a >> b >> k;
        if (k) {
            zielone[a].push_back(b);
            zielone[b].push_back(a);
        }
        else {
            czerwone[a].push_back(b);
            czerwone[b].push_back(a);
        }
    }
    
    for (int j = 0; j <=n; ++j) {
        d_kon_czerwone[j] = INT_MAX;
        d_kon_zielone[j] = INT_MAX;
    }
    
    d_kon_zielone[1] = 0;
    d_kon_czerwone[1] = 0;
    
    
    que.emplace(0,1,1);
    que.emplace(0,1,0);
    
    while(!que.empty()) {
        auto itr = que.begin();
        que.erase(itr);
        update_distance(get<1>(*itr), get<2>(*itr));
    }
    
    for (int l = 2; l <= n; ++l) {
         int value = min(d_kon_czerwone[l], d_kon_zielone[l]);
         if(value == INT_MAX)
             value = -1;
         cout << value << endl;
    }
}