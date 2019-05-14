#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    long long int n, d;
    cin >> n >> d;
    vector<long long int> tab;
    for (int i = 1; i <= n; ++i) {
        long long int k;
        cin >> k;
        tab.push_back(k);
    }
    
    
    sort(tab.begin(), tab.end());
    
    auto i = tab.begin();
    auto j = tab.begin();
    
    while (i != tab.end() && j != tab.end()) {
        if (*j - *i == d && i != j) {
            cout << *j << " " << *i;
            return 0;
        }
        else if (*j - *i <= d) {
            j++;
        }
        else {
            i++;
        }
    }
    
    cout << "NIE";
    
}