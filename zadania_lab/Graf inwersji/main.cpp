#include <iostream>
#include <vector>

using namespace std;
constexpr int MAXN = 1000001;

int main() {
    ios_base::sync_with_stdio(0);
    int per[MAXN];
    int n;
    
    cin >> n;
    vector<vector<int>> components;
    
    for (int i = 1; i <= n; ++i) {
        cin >> per[i];
    }
    
    int maxNumber = per[1];
    vector<int> pom;
    
    for (int i = 1; i <= n; ++i) {
        pom.push_back(i);
        maxNumber = max(maxNumber, per[i]);
        if (maxNumber == i) {
            components.push_back(pom);
            pom.clear();
        }
    }
    cout << components.size() << endl;
    for (auto const &vec : components) {
        cout << vec.size() << " ";
        for (auto i  : vec) {
            cout << i << " ";
        }
        cout << endl;
    }
}

