#include <iostream>
#include <vector>

using namespace std;

constexpr int MAXN = 500002;
int m, n;
int colour_tab[MAXN];
vector<int> edge[MAXN];

int DFS(int nr, int colour) {
    colour_tab[nr] = colour;
    for (auto v : edge[nr]) {
        if (colour_tab[v] == 0 && DFS(v, colour * (-1))) {
            return 1;
        } else if( colour_tab[v] == colour ){
            return 1;
        }
    }
    return 0;
}

int main_DFS() {
    for (int k = 1; k <= n; ++k) {
        if(colour_tab[k] == 0 && DFS(k,1)) {
            return 1;
        }
    }
    
    return 0;
}
int main() {
    ios_base::sync_with_stdio(0);
    
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        edge[x].push_back(y);
        edge[y].push_back(x);
    }
    
    for (int j = 1; j <= n; ++j) {
        colour_tab[j] = 0;
    }
    
    if(main_DFS()) {
        cout << "NIE";
    } else {
        cout << "TAK";
    }
    
}